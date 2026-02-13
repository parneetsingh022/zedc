#include <iostream>
#include <cstdint>

#include "opcodes.hpp"
#include "vm.hpp"


extern "C" void stdPrintInteger(VM* vm);
extern "C" void stdPrintChar(VM* vm);

int main(){
    uint8_t code[] = {
        BIPUSH, 72,
        BIPUSH, 101,
        SWP,
        DUP,

        CALL_NATIVE, 0,
        BIPUSH, 0xa,
        CALL_NATIVE, 1,

        CALL_NATIVE, 0,
        BIPUSH, 0xa,
        CALL_NATIVE, 1,

        CALL_NATIVE, 0,
        BIPUSH, 0xa,
        CALL_NATIVE, 1,

        HALT
    
    };

    VM vm; // Create an instance of the virtual machine
    vm.defineNative(stdPrintInteger); // Register the native function
    vm.defineNative(stdPrintChar); // Register the second native function

    vm.execute(code); // Execute the bytecode

    return 0;
}