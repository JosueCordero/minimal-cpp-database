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

        stream_file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
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

        if(page_number >= number_pages || page_number < 0){
            std::ostringstream oss;
            oss << "[Pager::loadPage] Page Number " << page_number 
            << " is out of range. Number of pages: " << number_pages
            << " Starting to count from page 0" << std::endl;
            throw PagError::page_out_of_range(oss.str());
        }
    
        if(pages.find(page_number) == pages.end()){
            pages[page_number] = RawMemory::Pointer(RawMemory::mallocPage(DBConfig::PAGE_SIZE));
            
            stream_file.seekg(page_number*DBConfig::PAGE_SIZE,std::ios::beg);
        
            stream_file.read(reinterpret_cast<char*>(pages[page_number].get()),DBConfig::PAGE_SIZE);
            if(!stream_file.good()){
                throw std::runtime_error("Fail to read the file");
            }
        }
    
        
    }else{
        throw std::runtime_error("Stream Integrity Compromized");
    }
    
}

void Pager::addPage(){
    if(stream_file.good()){
        stream_file.seekp(0,std::ios::end);  
        std::streampos pos = stream_file.tellp();
        if(pos == std::streampos(-1)){
            throw std::runtime_error("[Pager::addPage] Failed to get position with tellp()");
        }
        size_t new_file_lenght = static_cast<size_t>(pos) + DBConfig::PAGE_SIZE;
        
        if(new_file_lenght % DBConfig::PAGE_SIZE != 0){
            throw std::runtime_error(
                "DB is corrupt, the size of the file is not a multiple of the page size");
        }
        else{
            pages[number_pages] = RawMemory::Pointer(
                RawMemory::callocPage(DBConfig::PAGE_SIZE)
            );
            stream_file.write(reinterpret_cast<char*>(pages[number_pages].get()),DBConfig::PAGE_SIZE);
            if(!stream_file.good()){
                throw std::runtime_error("Fail to write to the file");
            }
            stream_file.flush();
            file_lenght = new_file_lenght;
            number_pages++;

        }
    }else{
        throw std::runtime_error("Stream Integrity Compromized");
    }
              
}

void Pager::flushPage(ulong page_number){
    if(pages.find(page_number) == pages.end()){
        std::ostringstream oss;
        oss << "[Pager::flushPage] Page Number " << page_number 
        << " is not in the program memory" << std::endl;
        throw PagError::page_out_of_range(oss.str());
    }

    if(stream_file.good()){
        stream_file.seekp(page_number*DBConfig::PAGE_SIZE,std::ios::beg);
        if(stream_file.fail()){
            throw std::runtime_error("Fail to seek the write position");
        }

        stream_file.write(reinterpret_cast<char*>(pages[page_number].get()),DBConfig::PAGE_SIZE);
        if(!stream_file.good()){
            throw std::runtime_error("Fail to write to the file");
        }
        stream_file.flush();
    }else{
        throw std::runtime_error("Stream Integrity Compromized");

    }
}



u_long Pager::getFileLenght(){
    return file_lenght;
}

void* Pager::getPage(u_long page_number){
    return pages[page_number].get();
}


