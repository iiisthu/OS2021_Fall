//
// Created by sharzy on 10/10/21.
//

#ifndef THREAD_1_OPERATION_H
#define THREAD_1_OPERATION_H

#include "model.h"
#include "embedding.h"
#include "instruction.h"

namespace proj1 {

using PayloadType = decltype(Instruction::payloads);

void op_init_emb(EmbeddingHolder &users, const EmbeddingHolder &items, const PayloadType &payload);
void op_update_emb(EmbeddingHolder &users, const EmbeddingHolder &items, int user_idx, int item_idx, int label);
Embedding* op_recommend(const EmbeddingHolder &users, const EmbeddingHolder &items, const PayloadType &payload);

void work(EmbeddingHolder &users, EmbeddingHolder &items, const Instructions &instructions);

} // namespace proj
#endif //THREAD_1_OPERATION_H
