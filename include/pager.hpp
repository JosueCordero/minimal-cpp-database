#ifndef PLUSMINI_DB_PAGER_HPP
#define PLUSMINI_DB_PAGER_HPP

#include <fstream>
#include <cstddef>
#include <vector>
#include <memory>



class Pager {
    public:
        Pager(const std::string& filename);

        //Getters and Setters
        unsigned long getFileLenght();
    private:
        std::fstream stream_file;
        size_t file_lenght; 
        unsigned long number_pages;

        struct FreeDeleter {
        void operator()(void* ptr) const {
            std::free(ptr);
        }
        };
    
        std::vector<std::unique_ptr<void, FreeDeleter>> pages;

};

#endif
