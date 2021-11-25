#include "model.h"
#include "utils.h"
#include "embedding.h"

namespace proj1 {

const double inf = 9999999.0;

double similarity(Embedding* embA, Embedding* embB) {
    double similarity = 0;
    double *vecA = embA->get_data();
    double *vecB = embB->get_data();
    for (int i = 0; i < embA->get_length(); ++i) {
        similarity += (vecA[i] - vecB[i]) * (vecA[i] - vecB[i]);
    }
    return similarity;
}

// NOTE: do not rely on this exact implementation -- it may get modified.
EmbeddingGradient* calc_gradient(Embedding* embA, Embedding* embB, int label) {
    /* For simplicity, here we just simulate the gradient backprop for:
        1. a dot product between embeddings
        2. a sigmoid activation function
        3. a binary cross entropy loss
    */
    embA->lock.read_lock();
    embB->lock.read_lock();
    if(label == -1) {
        label = embB->get_data()[0] > 1e-8? 0: 1;
    }
    double distance = similarity(embA, embB);
    embA->lock.read_unlock();
    double pred = sigmoid(distance);
    double loss = binary_cross_entropy_backward((double) label, pred);
    loss *= sigmoid_backward(distance);
    EmbeddingGradient *gradA = new Embedding((*embB) * loss);
    embB->lock.read_unlock();

    // Here we simulate a slow calculation
    a_slow_function(10);
    return gradA;
}

EmbeddingGradient* cold_start(Embedding* user, Embedding* item) {
    // Do some downstream work, e.g. let the user watch this video
    a_slow_function(10);
    // Then we collect a label, e.g. whether the user finished watching the video
    return calc_gradient(user, item, -1);
}

Embedding* recommend(Embedding* user, std::vector<Embedding*> items) {
    Embedding* maxItem;
    double sim, maxSim = -inf;
    user->lock.read_lock();
    for (auto item: items) {
        item->lock.read_lock();
        sim = similarity(user, item);
        item->lock.read_unlock();
        if (sim > maxSim) {
            maxItem = item;
            maxSim = sim;
        }
    }
    user->lock.read_unlock();
    return maxItem;
}

} // namespace proj1