#include "minidb_pp/pager.hpp"
#include "minidb_pp/buffer.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>



int main(int argc, char * argv[]){
    if(argc < 2){
        std::cout << "You should provide a file name" << std::endl;
        return EXIT_FAILURE;
    }
    Pager database(argv[1]);

    std::string user_name;
    std::string email;
    std::string color;

    std::size_t off_set = 0;

    if(database.getFileLenght()==0){
        std::cout << "Initializing Database with 1 page ..." << std::endl;
        database.addPage();

        std::cout << ">> Please enter your name" << std::endl << ">> ";
        InputBuffer::readInput(user_name);
        
        std::cout << ">> Please enter your email" << std::endl << ">> ";
        InputBuffer::readInput(email);
        
        std::cout << ">> Please enter your favorite color" << std::endl << ">> ";
        InputBuffer::readInput(color);

        std::size_t* raw_size = reinterpret_cast<std::size_t*>(database.getPage(0));
        char* raw_text = reinterpret_cast<char*>(database.getPage(0));

        *raw_size = user_name.size();
        off_set += sizeof(*raw_size); 

        strcpy(raw_text + off_set,user_name.c_str());
        off_set += user_name.size() + 1;

        raw_size = reinterpret_cast<std::size_t*>(raw_text + off_set);

        *raw_size = email.size();
        off_set += sizeof(*raw_size);
        
        strcpy(raw_text + off_set,email.c_str());
        off_set += email.size() + 1;

        raw_size = reinterpret_cast<std::size_t*>(raw_text + off_set);
        
        *raw_size = color.size();
        off_set += sizeof(*raw_size);
        
        strcpy(raw_text + off_set,color.c_str());        
       
        database.flushPage(0);

        std::cout << "Information Saved. Plase execute the command again to see your information" << std::endl;

        return EXIT_SUCCESS;
    }else{
        database.loadPage(0);

        std::size_t* raw_size = reinterpret_cast<std::size_t*>(database.getPage(0));
        char* raw_text = reinterpret_cast<char*>(database.getPage(0));

        user_name.assign(raw_text + sizeof(*raw_size),*raw_size);
        off_set += sizeof(*raw_size) + *raw_size + 1;

        raw_size = reinterpret_cast<std::size_t*>(raw_text + off_set);

        email.assign(raw_text + off_set + sizeof(*raw_size),*raw_size);
        off_set += sizeof(*raw_size) + *raw_size + 1;

        raw_size = reinterpret_cast<std::size_t*>(raw_text + off_set);

        color.assign(raw_text + off_set + sizeof(*raw_size),*raw_size);
        
        std::cout << "Hi " << user_name <<  "!" << std::endl;
        std::cout << "Your email is " << email << std::endl;
        std::cout << "And your favorite color is " << color << std::endl;
        
    }
    

    return EXIT_SUCCESS;
}