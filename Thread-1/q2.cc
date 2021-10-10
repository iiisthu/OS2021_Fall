// process `INIT_EMB` and `UPDATE_EMB`, `RECOMMEND` instructions concurrently

#include <fmt/core.h>

#include "lib/embedding.h"
#include "lib/instruction.h"
#include "lib/operation.h"

int main() {
    auto users = proj1::EmbeddingHolder("data/q2.in");
    auto items = proj1::EmbeddingHolder("data/q2.in");
    proj1::Instructions instructions = proj1::read_instructrions("data/q2_instruction.tsv");

    proj1::work(users, items, instructions);

    users.write_to_stdout();
    items.write_to_stdout();

    return 0;
}
