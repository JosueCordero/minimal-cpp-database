#ifndef PLUS_MINI_DB_TYPES_HPP
#define PLUS_MINI_DB_TYPES_HPP

#include <unordered_map>
#include <memory>
#include <cstdlib>
#include <cstddef>

struct FreeDeleter {
        void operator()(void* ptr) const {
            std::free(ptr);
        }
    };

namespace RawMemory {
    using Pointer = std::unique_ptr<void, FreeDeleter>;

    inline Pointer mallocPage(size_t size){
        void* ptr = std::malloc(size);
        if(!ptr) throw std::bad_alloc();
        return Pointer(ptr);
    }

    inline Pointer callocPage(size_t size){
        void* ptr = std::calloc(1,size);
        if(!ptr) throw std::bad_alloc();
        return Pointer(ptr);
    }
}

#endif