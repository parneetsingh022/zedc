#include "vm.hpp"
#include <iostream>


extern "C" void stdPrintInteger(VM* vm) {
    int32_t value = vm->pop(); // Pop the value to print from the stack
    std::cout << value; // Print the value
}

extern "C" void stdPrintChar(VM* vm) {
    // 1. Pop the 32-bit integer from the stack
    int32_t value = vm->pop(); 

    // 2. Convert (cast) it to a char and print it
    std::cout << static_cast<char>(value); 
}