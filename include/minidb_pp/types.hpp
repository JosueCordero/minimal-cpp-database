#ifndef PLUS_MINI_DB_TYPES_HPP
#define PLUS_MINI_DB_TYPES_HPP

#include <unordered_map>
#include <memory>
#include <cstdlib>

struct FreeDeleter {
        void operator()(void* ptr) const {
            std::free(ptr);
        }
    };

namespace RawMemory {
    using Pointer = std::unique_ptr<void, FreeDeleter>;
}

#endif