#include "vm.hpp"
#include <iostream>
#include <stdexcept>
#include "opcodes.hpp"

VM::VM() {
    sp = stack; // Initialize stack pointer to the base of the stack
    ip = nullptr; // Initialize instruction pointer to null
}

void VM::execute(const uint8_t* code) {
    ip = code; // Set instruction pointer to the start of the code
    while (true) {
        uint8_t opcode = fetch(); // Fetch next opcode
        switch (opcode) {
            case NOP:
                break; // No operation, just continue to next instruction
            case IPUSH: {
                // Read 4 bytes for the integer
                int32_t value = (fetch() << 24)  | 
                                (fetch() << 16)  | 
                                (fetch() << 8)   | 
                                 fetch(); 
                push(value); // Push the integer onto the stack
                break;
            }
            case BIPUSH: {
                // Read 1 byte for the integer
                int8_t value = static_cast<int8_t>(fetch());
                push(static_cast<int32_t>(value)); // Push the integer onto the stack
                break;
            }

            case IPOP: {
                pop(); // Pop the top value from the stack and discard it
                break;
            }
  
            case IADD: {
                int32_t b = pop(); // Pop top value
                int32_t a = pop(); // Pop next value
                push(a + b); // Push the result of addition back onto the stack
                break;
            }

            case ISUB: {
                int32_t b = pop(); // Pop top value
                int32_t a = pop(); // Pop next value
                push(a - b); // Push the result of subtraction back onto the stack
                break;
            }

            case IMUL: {
                int32_t b = pop(); // Pop top value
                int32_t a = pop(); // Pop next value
                push(a * b); // Push the result of multiplication back onto the stack
                break;
            }

            case IDIV: {
                int32_t b = pop(); // Pop top value
                int32_t a = pop(); // Pop next value
                if (b == 0) {
                    throw std::runtime_error("Division by zero"); // Check for division by zero
                }
                push(a / b); // Push the result of division back onto the stack
                break;
            }

            case IMOD: {
                int32_t b = pop(); // Pop top value
                int32_t a = pop(); // Pop next value
                if (b == 0) {
                    throw std::runtime_error("Division by zero"); // Check for division by zero
                }
                push(a % b); // Push the result of modulus back onto the stack
                break;
            }

            case CALL_NATIVE: {
                // 1. Fetch the index of the native function from the bytecode
                uint8_t native_index = fetch(); 

                // 2. Safety check: does this index exist in our vector?
                if (native_index < native_functions.size()) {
                    // 3. Call the function! (Remember: NativeFn is a pointer to a function)
                    native_functions[native_index](this); 
                } else {
                    throw std::runtime_error("Native function index out of bounds");
                }
                break;
            }

            case SWP : {
                int32_t a = pop(); // Pop top value
                int32_t b = pop(); // Pop next value
                push(a); // Push the first popped value back onto the stack
                push(b); // Push the second popped value back onto the stack
                break;
            }

            case DUP : {
                int32_t a = pop(); // Pop top value
                push(a); // Push it back onto the stack
                push(a); // Push it again to duplicate
                break;
            }


            case ISTORE: {
                // 1. Fetch two bytes to create a 16-bit index (Big Endian)
                uint16_t index = (static_cast<uint16_t>(fetch()) << 8) | fetch(); 
                int32_t value = pop();

                // 2. Dynamic Resize: If the index is new, expand the closet
                if (index >= storage.size()) {
                    storage.resize(index + 1, 0); // Initialize new slots with 0
                }
                
                storage[index] = value;
                break;
            }

            case ILOAD: {
                // 1. Must also fetch two bytes to match ISTORE
                uint16_t index = (static_cast<uint16_t>(fetch()) << 8) | fetch(); 

                // 2. Safety Check: Since storage is dynamic, we check if it exists
                if (index < storage.size()) {
                    push(storage[index]);
                } else {
                    // If they try to load a variable that was never stored, 
                    // we can either throw an error or just push 0.
                    throw std::runtime_error("Accessing uninitialized local variable");
                }
                break;
            }

            case HALT:
                return; // Stop execution
            default:
                throw std::runtime_error("Unknown opcode"); // Handle unknown opcode
        }
    }
}

void VM::push(int32_t value) {
    if (sp - stack >= STACK_SIZE) {
        throw std::runtime_error("Stack overflow"); // Check for stack overflow
    }
    *sp++ = value; // Push value onto the stack and move stack pointer
}

int32_t VM::pop() {
    if (sp == stack) {
        throw std::runtime_error("Stack underflow"); // Check for stack underflow
    }
    return *--sp; // Move stack pointer back and return the value
}

uint8_t VM::fetch() {
    return *ip++; // Return the current byte and move instruction pointer to the next byte
}

void VM::defineNative(NativeFn func) {
    native_functions.push_back(func);
}