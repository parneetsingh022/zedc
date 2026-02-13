#include <iostream>
#include <cstdint>

#include "opcodes.hpp"
#include "vm.hpp"


extern "C" void stdPrintInteger(VM* vm);
extern "C" void stdPrintChar(VM* vm);

int main(){
    uint8_t code[] = {
        IPUSH, 0x00, 0x00, 0x00, 0x05, // Push 5
        IPUSH, 0x00, 0x00, 0x00, 0x03, // Push 3
        IADD,                          // Add top two values
        CALL_NATIVE, 0x00,             // Call the first native function (stdPrintInteger)
        IPUSH, 0x00, 0x00, 0x00, 0x0a, // Push 10 (ASCII for newline)
        CALL_NATIVE, 0x01,             // Call the second native function (stdPrintChar)
        HALT                           // Stop execution
    };

    VM vm; // Create an instance of the virtual machine
    vm.defineNative(stdPrintInteger); // Register the native function
    vm.defineNative(stdPrintChar); // Register the second native function

    vm.execute(code); // Execute the bytecode

    return 0;
}