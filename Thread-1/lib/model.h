#ifndef THREAD_LIB_MODEL_H_
#define THREAD_LIB_MODEL_H_

#include <vector>
#include "embedding.h"

namespace proj1 {

/* NOTE: DO NOT rely on the implementation here. We may
         change the implemenation details.
*/
double similarity(Embedding* entityA, Embedding* entityB);

EmbeddingGradient* calc_gradient(Embedding* entityA, Embedding* entityB, int label);

EmbeddingGradient* cold_start(Embedding* newUser, Embedding* item);

Embedding* recommend(Embedding* user, std::vector<Embedding*> items);

} // namespace proj1

#endif // THREAD_LIB_MODEL_H_