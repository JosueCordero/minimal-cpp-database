#include "minidb_pp/buffer.hpp"
#include <iostream>
#include <string>



bool InputBuffer::readInput(){
    if(!std::getline(std::cin, this->buffer)){
        return false;
    } 
    return true;   
}

bool InputBuffer::readInput(std::string& external_buffer){
    if(!std::getline(std::cin, external_buffer)){
        return false;
    } 
    return true;   
}

const std::string& InputBuffer::getBuffer() const {
    return buffer;
}