#ifndef THREAD_LIB_EMBEDDING_H_
#define THREAD_LIB_EMBEDDING_H_

#include <string>
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <typeinfo>

namespace proj1 {

enum EMBEDDING_ERROR {
    LEN_MISMATCH = 0,
    NON_POSITIVE_LEN
};

class RWLock {
    public:
        int AR=0, WW=0, AW=0, WR=0;
        std::mutex *mtx;
        std::condition_variable *okread;
        std::condition_variable *okwrite;
        RWLock(){
            mtx = new std::mutex;
            okread = new std::condition_variable;
            okwrite = new std::condition_variable;
        }

        ~RWLock() {
            delete mtx;
            delete okread;
            delete okwrite;
        }
        
        void read_lock() {
            std::unique_lock<std::mutex> lck(*mtx);
            //printf("Start read lock\n");
            while ((this->AW + this->WW) > 0) {
                this->WR ++;
                this->okread->wait(lck);
                this->WR --;
            }
            this->AR ++;
            lck.unlock();
            //printf("Finish read lock\n");
        }

        void read_unlock() { 
            std::unique_lock<std::mutex> lck(*mtx);
            //printf("Start read unlock\n");
            this->AR --;
            if(this->AR == 0 && this->WW > 0)
                this->okwrite->notify_all();
            lck.unlock();
            //printf("Finish read unlock\n");
        }

        void write_lock() {
            std::unique_lock<std::mutex> lck(*mtx);
            //printf("Start write lock\n");
            while ((this->AW + this->AR) > 0) {
                this->WW ++;
                this->okwrite->wait(lck);
                this->WW --;
            }
            this->AW ++;
            lck.unlock();
            //printf("Finish write lock\n");
        }

        void write_unlock() {
            std::unique_lock<std::mutex> lck(*mtx);
            //printf("Start write unlock\n");
            this->AW --;
            if (this->WW > 0)
                this->okwrite->notify_all();
            else if (this->WR > 0)
                this->okread->notify_all();
            lck.unlock();
            //printf("Finish write unlock\n");
        }

    private:
        
        //volatile std::atomic<int> AR=0, WW=0, AW=0, WR=0; is a possible choice
};

class Embedding{
public:
    RWLock lock = RWLock();
    Embedding(){}
    Embedding(int);  // Random init an embedding
    Embedding(int, double*);
    Embedding(int, std::string);
    Embedding(Embedding*);
    ~Embedding() { delete []this->data; }
    double* get_data() { return this->data; }
    int get_length() { return this->length; }
    void update(Embedding*, double);
    std::string to_string();
    void write_to_stdout();
    // Operators
    Embedding operator+(const Embedding&);
    Embedding operator+(const double);
    Embedding operator-(const Embedding&);
    Embedding operator-(const double);
    Embedding operator*(const Embedding&);
    Embedding operator*(const double);
    Embedding operator/(const Embedding&);
    Embedding operator/(const double);
    bool operator==(const Embedding&);
private:
    double* data;
    int length;
};

using EmbeddingMatrix = std::vector<Embedding*>;
using EmbeddingGradient = Embedding;

class EmbeddingHolder{
public:
    RWLock lock = RWLock();
    EmbeddingHolder(std::string filename);
    EmbeddingHolder(EmbeddingMatrix &data);
    ~EmbeddingHolder();
    static EmbeddingMatrix read(std::string);
    void write_to_stdout();
    void write(std::string filename);
    int append(Embedding *data);
    void update_embedding(int, EmbeddingGradient*, double);
    Embedding* get_embedding(int idx) const { return this->emb_matx[idx]; } 
    unsigned int get_n_embeddings() { return this->emb_matx.size(); }
    int get_emb_length() {
        return this->emb_matx.empty()? 0: this->get_embedding(0)->get_length();
    }
    bool operator==(const EmbeddingHolder&);
private:
    EmbeddingMatrix emb_matx;
};

} // namespace proj1
#endif // THREAD_LIB_EMBEDDING_H_