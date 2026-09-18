/*
    DenseErasure.hpp

    Declaration of a struct containing dense vector erasure information.
*/

#pragma once

#include <cstddef>

namespace toxico {
    struct DenseErasure {
        // If a move occured
        bool moved = false;

        // The index that the swapped item went to/from
        std::size_t moved_from = 0;
        std::size_t moved_to = 0;
    };
}
