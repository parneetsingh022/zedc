#include "vm.hpp"
#include <iostream>


extern "C" void stdPrintInteger(VM* vm) {
    int32_t value = vm->pop();
    std::cout << value;
}

extern "C" void stdPrintChar(VM* vm) {
    int32_t value = vm->pop(); 
    std::cout << static_cast<char>(value); 
}