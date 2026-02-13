#ifndef VM_HPP
#define VM_HPP

#include <cstdint>
#include <vector>

#define STACK_SIZE 1024

class VM;

typedef void (*NativeFn)(VM* vm);

class VM {
    public:
        VM();
        void execute(const uint8_t* code);
        void defineNative(NativeFn func);

        void push(int32_t value); // push 32-bit integer onto the stack
        int32_t pop(); // pop 32-bit integer from the stack
        uint8_t fetch(); // fetch next byte from code
    private:
        // Vector to hold native functions
        std::vector<NativeFn> native_functions;

        // Stack for operands
        int32_t stack[STACK_SIZE];
        int32_t* sp; // Stack pointer
        // Instruction pointer
        const uint8_t* ip;
};

#endif // VM_HPP