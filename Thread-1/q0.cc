#include <vector>
#include <tuple>

#include <string>   // string
#include <chrono>   // timer
#include <iostream> // cout, endl

#include "lib/utils.h"
#include "lib/model.h" 
#include "lib/embedding.h" 
#include "lib/instruction.h"
#include "lib/operation.h"

namespace proj1 {

void run_one_instruction(const Instruction &inst, EmbeddingHolder &users, const EmbeddingHolder &items) {
    switch(inst.order) {
        case INIT_EMB: {
            op_init_emb(users, items, inst.payloads);
            break;
        }
        case UPDATE_EMB: {
            // read users[user_idx], items[item_idx], update users[user_idx]
            int user_idx = inst.payloads[0];
            int item_idx = inst.payloads[1];
            int label = inst.payloads[2];
            op_update_emb(users, items, user_idx, item_idx, label);
            break;
        }
        case RECOMMEND: {
            // read users[user_idx], read items[item_idx...]
            op_recommend(users, items, inst.payloads)->write_to_stdout();
            break;
        }
    }

}

} // namespace proj1

int main(int argc, char *argv[]) {
    auto users = proj1::EmbeddingHolder("data/q0.in");
    auto items = proj1::EmbeddingHolder("data/q0.in");
    proj1::Instructions instructions = proj1::read_instructrions("data/q0_instruction.tsv");

    {
        proj1::AutoTimer timer("q0");  // using this to print out timing of the block
        // Run all the instructions
        for (const proj1::Instruction& inst: instructions) {
            proj1::run_one_instruction(inst, users, items);
        }
    }

    // Write the result
    users.write_to_stdout();
    items.write_to_stdout();

    return 0;
}
