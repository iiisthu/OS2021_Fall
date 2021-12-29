#include <vector>
#include <tuple>

#include <string>   // string
#include <chrono>   // timer
#include <iostream> // cout, endl
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

#include "lib/utils.h"
#include "lib/model.h" 
#include "lib/embedding.h" 
#include "lib/instruction.h"

namespace proj1 {

void Coldstart(EmbeddingHolder* users, Embedding* new_user, Embedding* item_emb, int user_idx) {
    // Call cold start for downstream applications, slow

    EmbeddingGradient* gradient = cold_start(new_user, item_emb);

    new_user->lock.write_lock();
    users->update_embedding(user_idx, gradient, 0.01);
    new_user->lock.write_unlock();
    delete gradient;
}

void run_one_instruction(Instruction inst, EmbeddingHolder* users, EmbeddingHolder* items) {
    switch(inst.order) {
        case INIT_EMB: {
            // We need to init the embedding
            users->lock.read_lock();
            int length = users->get_emb_length();
            users->lock.read_unlock();

            Embedding* new_user = new Embedding(length);

            users->lock.write_lock();
            int user_idx = users->append(new_user);
            users->lock.write_unlock();

            std::vector<std::thread *> multiple_coldstarts;
            
            for (int item_index: inst.payloads) {
                Embedding* item_emb = items->get_embedding(item_index);
                std::thread *t = new std::thread(Coldstart, users, new_user, item_emb, user_idx);
                multiple_coldstarts.push_back(t);
            }
            int len = multiple_coldstarts.size();
            for (int j=0;j<len;++j) 
                multiple_coldstarts[j]->join();

            break;
        }
        case UPDATE_EMB: {
            int user_idx = inst.payloads[0];
            int item_idx = inst.payloads[1];
            int label = inst.payloads[2];
            // You might need to add this state in other questions.
            // Here we just show you this as an example
            // int epoch = -1;
            //if (inst.payloads.size() > 3) {
            //    epoch = inst.payloads[3];
            //}
            Embedding* user = users->get_embedding(user_idx);
            Embedding* item = items->get_embedding(item_idx);

            
            EmbeddingGradient* gradient = calc_gradient(user, item, label);
            user->lock.write_lock();
            users->update_embedding(user_idx, gradient, 0.01);
            user->lock.write_unlock();
            delete gradient;

            
            gradient = calc_gradient(item, user, label);
            item->lock.write_lock();
            items->update_embedding(item_idx, gradient, 0.001);
            item->lock.write_unlock();
            delete gradient;

            break;
        }
        case RECOMMEND: {
            int user_idx = inst.payloads[0];
            Embedding* user = users->get_embedding(user_idx);
            std::vector<Embedding*> item_pool;
            int iter_idx = inst.payloads[1];
            for (unsigned int i = 2; i < inst.payloads.size(); ++i) {
                int item_idx = inst.payloads[i];
                item_pool.push_back(items->get_embedding(item_idx));
            }
            Embedding* recommendation = recommend(user, item_pool);
            recommendation->write_to_stdout();
            break;
        }
    }

}

} // namespace proj1

int main(int argc, char *argv[]) {

    proj1::EmbeddingHolder* users = new proj1::EmbeddingHolder("data/q2.in");
    proj1::EmbeddingHolder* items = new proj1::EmbeddingHolder("data/q2.in");
    proj1::Instructions instructions = proj1::read_instructrions("data/q2_instruction.tsv");
    {
    proj1::AutoTimer timer("q2");  // using this to print out timing of the block

    // Run all the instructions
    std::vector<std::thread *> threadArr;
    for (proj1::Instruction inst: instructions) {
        //printf("%d\n", threadArr.size());
        std::thread *t = new std::thread(proj1::run_one_instruction, inst, users, items);
        threadArr.push_back(t);
    }
    int len = threadArr.size();
    for (int j=0;j<len;++j) 
        threadArr[j]->join();
    }

    // Write the result
    users->write_to_stdout();
    items->write_to_stdout();

    // We only need to delete the embedding holders, as the pointers are all
    // pointing at the emb_matx of the holders.
    delete users;
    delete items;

    return 0;
}