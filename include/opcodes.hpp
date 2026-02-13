
#ifndef OPCODES_HPP
#define OPCODES_HPP


#define NOP           0x00
#define HALT          0x01

#define IPUSH         0x02
#define IPOP          0x03
// Arithmetic operations
#define IADD          0x04
#define ISUB          0x05
#define IMUL          0x06
#define IDIV          0x07
#define IMOD          0x08

#define CALL_NATIVE   0x09

#endif // OPCODES_HPP