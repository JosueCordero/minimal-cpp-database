#ifndef PLUS_MINI_DB_BUFFER_HPP
#define PLUS_MINI_DB_BUFFER_HPP

#include <cstddef>
#include <string>

class InputBuffer {
    public:
        InputBuffer() = default;
        bool readInput();
        static bool readInput(std::string& external_buffer);

        const std::string& getBuffer() const;

    private:
        std::string buffer;
        

};

#endif

