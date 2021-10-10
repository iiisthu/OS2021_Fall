#include <vector>
#include <tuple>

#include <string>   // string
#include <chrono>   // timer
#include <iostream> // cout, endl

#include "lib/utils.h"
#include "lib/model.h" 
#include "lib/embedding.h" 
#include "lib/instruction.h"

namespace proj1 {

void run_one_instruction(Instruction inst, EmbeddingHolder* users, EmbeddingHolder* items) {
    switch(inst.order) {
        case INIT_EMB: {
            // read items[item_idx...], write a new user
            // We need to init the embedding
            int length = users->get_emb_length();
            auto* new_user = new Embedding(length);
            int user_idx = users->append(new_user);
            for (int item_index: inst.payloads) {
                Embedding* item_emb = items->get_embedding(item_index);
                // Call cold start for downstream applications, slow
                EmbeddingGradient* gradient = cold_start(new_user, item_emb);
                users->update_embedding(user_idx, gradient, 0.01);
            }
            break;
        }
        case UPDATE_EMB: {
            // read users[user_idx], items[item_idx], update users[user_idx]
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
            users->update_embedding(user_idx, gradient, 0.01);
            break;
        }
        case RECOMMEND: {
            // read users[user_idx], read items[item_idx...]
            int user_idx = inst.payloads[0];
            Embedding* user = users->get_embedding(user_idx);
            std::vector<Embedding*> item_pool;
            for (unsigned int i = 1; i < inst.payloads.size(); ++i) {
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
    auto* users = new proj1::EmbeddingHolder("data/q0.in");
    auto* items = new proj1::EmbeddingHolder("data/q0.in");
    proj1::Instructions instructions = proj1::read_instructrions("data/q0_instruction.tsv");
    {
    proj1::AutoTimer timer("q0");  // using this to print out timing of the block
    // Run all the instructions
    for (const proj1::Instruction& inst: instructions) {
        proj1::run_one_instruction(inst, users, items);
    }
    }

    // Write the result
    users->write_to_stdout();
    items->write_to_stdout();

    return 0;
}
