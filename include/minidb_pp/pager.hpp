#ifndef PLUSMINI_DB_PAGER_HPP
#define PLUSMINI_DB_PAGER_HPP

#include "minidb_pp/types.hpp"
#include <fstream>
#include <cstddef>
#include <unordered_map>
#include <memory>


class Pager {
    public:
        Pager(const std::string& filename);
        ~Pager();

        void loadPage(u_long page_number);
    
        //Getters and Setters
        u_long getFileLenght();
        RawMemory::Pointer& getPage();
    private:
        std::fstream stream_file;
        size_t file_lenght; 
        u_long number_pages;

        std::unordered_map<u_long, RawMemory::Pointer> pages;

};

#endif
