# Endianness Explained 🧠

**Endianness** refers to the byte ordering used to store data in memory.

## Core Concepts

### Byte Ordering Types

1. **Little-Endian**

   - Least significant byte (LSB) at lowest address
   - Dominant in x86, ARM, RISC-V

2. **Big-Endian**

   - Most significant byte (MSB) at lowest address
   - Used in network protocols, PowerPC, SPARC

3. **Bi-Endian**
   - Configurable at runtime (some ARM cores)

Below is an interactive demo in C showing byte ordering in memory:

## What's Here

- [`main.c`](./main.c) - Runs little/big endian visualization

## Quick Start

```bash
gcc main.c -o endian_demo
./endian_demo
```
