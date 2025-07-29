#include "minidb_pp/constants.hpp"
#include "minidb_pp/pager.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept> 
#include <unordered_map>
#include <cstdlib>

Pager::Pager(const std::string& filename){
    stream_file.open(filename, std::ios::in | std::ios::out | std::ios::binary);

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

Pager::~Pager(){
    if(stream_file.is_open()){
        std::cout << "closing stream" << std::endl;
        stream_file.close();
    }
}

void Pager::loadPage(u_long page_number){
    if(stream_file.good()){

        if(page_number >= number_pages && page_number < 0){
            std::ostringstream oss;
            oss << "[Pager::loadPage] Page Number " << page_number 
            << " is out of range. Max page number is " << number_pages
            << " and Min number is 0";
            throw std::out_of_range(oss.str());
        }
    
        if(pages.find(page_number) == pages.end()){
            pages[page_number] = RawMemory::Pointer(std::malloc(DBConfig::PAGE_SIZE));
        }
    
        stream_file.seekg(page_number*DBConfig::PAGE_SIZE,std::ios::beg);
    
        stream_file.read(reinterpret_cast<char*>(pages[page_number].get()),DBConfig::PAGE_SIZE);
        if(!stream_file.good()){
            throw std::runtime_error("Fail to read the file");
        }
        
    }else{
        throw std::runtime_error("Stream Integrity Compromized");
    }
    
}

u_long Pager::getFileLenght(){
    return file_lenght;
}



