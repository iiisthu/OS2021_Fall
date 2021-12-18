#include <gtest/gtest.h>
#include<vector>
#include<thread>
#include<string>

#include "lib/array_list.h"
#include "lib/mma_client.h"
#include "lib/mma_server.h"

namespace proj4 {
namespace testing{

class MMATestA : public ::testing::Test {
 protected:
  void SetUp() override {
    server_thread = new std::thread(&RunServerUL, 10);
    server_thread->detach();
    sleep(1);

    std::string target_str = "localhost:50051";
    mma = new MmaClient(
        grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

    workload_sz_1 = 4000; 
    workload_sz_2 = 2000; 
    workload_sz_3 = 100; 
    workload_sz_4 = 2000;
    metrix_length = 10;
    loop_times = 10;
    thread_num = 20;
  }
  void TearDown() override {ShutdownServer(); delete mma;}
    size_t workload_sz_1;
    size_t workload_sz_2;
    size_t workload_sz_3;
    size_t workload_sz_4;
    int metrix_length;
    int loop_times;
    int thread_num;
    MmaClient* mma;
    std::thread* server_thread;
    std::vector<std::vector<int>>metrix = {{ 2850, 2895, 2940, 2985, 3030, 3075, 3120, 3165, 3210, 3255 },
    { 7350, 7495, 7640, 7785, 7930, 8075, 8220, 8365, 8510, 8655 },
    { 11850, 12095, 12340, 12585, 12830, 13075, 13320, 13565, 13810, 14055 },
    { 16350, 16695, 17040, 17385, 17730, 18075, 18420, 18765, 19110, 19455 },
    { 20850, 21295, 21740, 22185, 22630, 23075, 23520, 23965, 24410, 24855 },
    { 25350, 25895, 26440, 26985, 27530, 28075, 28620, 29165, 29710, 30255 },
    { 29850, 30495, 31140, 31785, 32430, 33075, 33720, 34365, 35010, 35655 },
    { 34350, 35095, 35840, 36585, 37330, 38075, 38820, 39565, 40310, 41055 },
    { 38850, 39695, 40540, 41385, 42230, 43075, 43920, 44765, 45610, 46455 },
    { 43350, 44295, 45240, 46185, 47130, 48075, 49020, 49965, 50910, 51855 },};
};

class MMATestB : public ::testing::Test {
 protected:
  void SetUp() override {
    server_thread = new std::thread(&RunServerL, 10, 20);
    server_thread->detach();
    sleep(1);

    std::string target_str = "localhost:50051";
    mma = new MmaClient(
        grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

    workload_sz = 2000;
    thread_num = 20;
  }
  void TearDown() override {ShutdownServer(); delete mma;}
    size_t workload_sz;
    int thread_num;
    MmaClient* mma;
    std::thread* server_thread;
};

TEST_F(MMATestA,task1){
	ArrayList* arr = mma->Allocate(workload_sz_1);
    for(unsigned long i = 0; i<workload_sz_1; i++){
        arr->Write(i, 1);
    }
    for(unsigned long i = 0; i<workload_sz_1; i++){
        EXPECT_EQ(1, arr->Read(i));
    }
    mma->Free(arr);
}

TEST_F(MMATestA,task2){
	std::vector<ArrayList*>arr;
    for(int i = 0; i<loop_times; i++){
        arr.push_back(mma->Allocate(workload_sz_2));
        for(unsigned long j = 0; j < workload_sz_2; j++)arr[i]->Write(j, i);
    }
    for(int i = 0; i<loop_times; i++){
        if(i %2)mma->Free(arr[i]);
        else for(unsigned long j = 0; j < workload_sz_2; j++)EXPECT_EQ(i, arr[i]->Read(j));
    }
    for(int i = 0; i<loop_times; i++){
        if(i %2 == 0)mma->Free(arr[i]);
    }
}

TEST_F(MMATestA,task3){
	std::vector<ArrayList*>metrixA, metrixB, metrixC;
    for(int i = 0; i<metrix_length; i++){
        metrixA.push_back(mma->Allocate(metrix_length));
        metrixB.push_back(mma->Allocate(metrix_length));
        metrixC.push_back(mma->Allocate(metrix_length));
        for(int j = 0; j < metrix_length; j++){
            metrixA[i]->Write(j, i*metrix_length+j);
            metrixB[i]->Write(j, i*metrix_length+j);
            metrixC[i]->Write(j, 0);
        }
    }
    
    for(int i = 0; i<metrix_length; i++){
        for(int j = 0; j<metrix_length; j++){
            for(int k = 0; k < metrix_length; k++){
                metrixC[i]->Write(j, metrixC[i]->Read(j)+metrixA[i]->Read(k)*metrixB[k]->Read(j));
            }
        }
    }

    for(int i = 0; i<metrix_length; i++){
        for(int j = 0; j<metrix_length; j++){
            EXPECT_EQ(metrix[i][j], metrixC[i]->Read(j));
        }
    }

    for(int i = 0; i<metrix_length; i++){
        mma->Free(metrixA[i]);
        mma->Free(metrixB[i]);
        mma->Free(metrixC[i]);
    }

}

void workload(MmaClient * my_mma, size_t workload_sz){
    ArrayList* arr = my_mma->Allocate(workload_sz);
    for(unsigned long j = 0; j < workload_sz; j++)arr->Write(j, j);
    for(unsigned long j = 0; j < workload_sz; j++)EXPECT_EQ(j, arr->Read(j));
    my_mma->Free(arr);
}

TEST_F(MMATestA,task4){
    std::vector<std::thread*> pool;
    for(int i = 0; i<thread_num; i++) {
        pool.push_back(new std::thread(&workload, mma, workload_sz_4));
    }

    for (auto t: pool) {
        t->join();
    }
}

TEST_F(MMATestB,task5){
    std::vector<std::thread*> pool;
    for(int i = 0; i<thread_num; i++) {
        pool.push_back(new std::thread(&workload, mma, workload_sz));
    }

    for (auto t: pool) {
        t->join();
    }
}

} // namespace testing
} // namespace proj4

int main(int argc,char **argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
