#ifndef PLUSMINI_DB_PAGER_HPP
#define PLUSMINI_DB_PAGER_HPP

#include "minidb_pp/types.hpp"
#include <fstream>
#include <cstddef>
#include <unordered_map>
#include <memory>
#include <exception>
#include <string>


class Pager {
    public:
        Pager(const std::string& filename);
        ~Pager();

        void loadPage(u_long page_number);
        void addPage();

        //Getters and Setters
        u_long getFileLenght();
        void* getPage(u_long page_number);
    private:
        std::fstream stream_file;
        size_t file_lenght; 
        u_long number_pages;

        std::unordered_map<u_long, RawMemory::Pointer> pages;

};

namespace PagError {

    class page_out_of_range : public std::exception {
        private:
            std::string message;
        public:
            page_out_of_range(const std::string& filename)
            : message("Failed to read file" + filename) {} 
            
            const char* what() const noexcept override {
                return message.c_str();
            }  
    };
}

#endif
