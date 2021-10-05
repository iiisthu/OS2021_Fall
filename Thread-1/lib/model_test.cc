#include <gtest/gtest.h>
#include <chrono>
#include "model.h"

namespace proj1 {
namespace testing{

class ModelTest : public ::testing::Test {
 protected:
  void SetUp() override {
    double embA[20] = {-0.9166718150866153,0.43829227278389205,-0.6129205231425989,0.7738693110376684,-0.04456069156634124,0.8807831166061564,-0.8206278700342509,0.5013513447020947,0.8570578529268591,0.3906799520892723,0.6558968505921785,0.0011654760044317314,0.3008835791217257,-0.15983430198414705,-0.0693333837225647,-0.6526558237637923};
    double embB[20] = {0.9210598583969818,0.42579710374854174,0.4036360259825613,0.030714658443632636,-0.885772459758438,-0.24727514094877123,0.7355606108008894,0.10546495518591437,-0.8023562184533268,-0.49625645997262624,-0.9207327565798142,-0.5815206606673406,0.9351907452001367,0.3172382122419557,0.003001769800845988,-0.922981014248552};
	emb_testA = new Embedding(20, embA);  
	emb_testB = new Embedding(20, embB);   
  }
  Embedding* emb_testA;
  Embedding* emb_testB;
};

TEST_F(ModelTest, test_calc_gradient){
	auto start = std::chrono::high_resolution_clock::now();
	calc_gradient(emb_testA, emb_testB, 1);
    auto end = std::chrono::high_resolution_clock::now();
    auto time_ellapsed = end - start;
	EXPECT_LT(10*1000, time_ellapsed.count());
}

TEST_F(ModelTest, test_cold_start){
	auto start = std::chrono::high_resolution_clock::now();
	cold_start(emb_testA, emb_testB);
    auto end = std::chrono::high_resolution_clock::now();
    auto time_ellapsed = end - start;
	EXPECT_LT(20*1000, time_ellapsed.count());
}

} // namespace testing
} // namespace proj1

int main(int argc,char **argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
