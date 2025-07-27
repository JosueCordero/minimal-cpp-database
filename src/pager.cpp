#include "constants.hpp"
#include "pager.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept> 

Pager::Pager(const std::string& filename){
    stream_file.open(filename, std::ios::in | std::ios::out);

    if(!stream_file.is_open()){
        stream_file.clear();
        stream_file.open(filename, std::ios::out);
        stream_file.close();

        stream_file.open(filename, std::ios::in | std::ios::out);
        if(!stream_file.is_open()){
            throw std::runtime_error("Fail to open the file");
        }
    }

    stream_file.seekg(0, std::ios::end);
    file_lenght = static_cast<size_t>(stream_file.tellg());

    if(file_lenght % DBConfig::PAGE_SIZE != 0){
        throw std::runtime_error(
            "DB is corrupt, the size of the file is not a multiple of the page size");
    }
    number_pages = file_lenght / DBConfig::PAGE_SIZE; 
}

unsigned long Pager::getFileLenght(){
    return file_lenght;
}

