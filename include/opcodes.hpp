
#ifndef OPCODES_HPP
#define OPCODES_HPP


#define NOP           0x00
#define HALT          0x01

#define IPUSH         0x02
#define IPOP          0x03
#define BIPUSH        0x04 // Push a byte as an integer onto the stack
// Arithmetic operations
#define IADD          0x05
#define ISUB          0x06
#define IMUL          0x07
#define IDIV          0x08
#define IMOD          0x09

#define CALL_NATIVE   0x0a

#define SWP          0x0b // Swap the top two values on the stack
#define DUP          0x0c // Duplicate the top value on the stack

#define ILOAD        0x0d // Load an integer from a local variable
#define ISTORE       0x0e // Store an integer into a local variable

#endif // OPCODES_HPP