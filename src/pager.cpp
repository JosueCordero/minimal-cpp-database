#include "pager.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept> 

Pager::Pager(const std::string& filename){
    stream_file.open(filename, std::ios::in | std::ios::out);

    if(!stream_file.is_open()){
        throw std::runtime_error("File fail to open");
    }

    stream_file.seekg(0, std::ios::end);

    file_lenght = static_cast<size_t>(stream_file.tellg());
}

unsigned long Pager::getFileLenght(){
    return file_lenght;
}

