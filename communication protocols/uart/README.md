# UART Communication Overview 📡

**UART** (Universal Asynchronous Receiver Transmitter) is a serial communication protocol that transmits data without a shared clock signal between the transmitter and receiver. However, for a success data transfer, both devices must agree on these things:

## Required Settings

1. **Baud Rate**

   - Transmission speed (bits per second)
   - Must match on both devices

2. **Parity**

   - Basic error-detection method that adds a single bit to each data frame
   - **How it works**:

     1. Transmitter counts 1s in the data bits
     2. Adds parity bit to make the total 1s either even or odd
     3. Receiver verifies the total 1s match the expected parity
        Options:

     - **None**: No error checking
     - **Odd**: Total 1s (data + parity) must be odd
     - **Even**: Total 1s must be even

     **Error Detection**:

     - Receiver counts all 1s in received data + parity bit
     - If count doesn't match parity setting:
       - **Odd parity**: Even number of 1s → Error
       - **Even parity**: Odd number of 1s → Error

## Communication Process

- **Idle State**

  - Line is held high (1) when no transmission occurs - This state indicates no data being sent

- **Start Bit**
- Transmitter pulls line low (0) for one bit period
- Signals the beginning of a data frame
- Receiver detects this falling edge to synchronize timing

- **Data Bits**

  - Actual payload (5-9 bits, usually 8)
  - LSB (Least Significant Bit) transmitted first

- **Parity Bit (Optional)**

  - Single bit added for basic error detection
  - Type determined by parity setting (Odd/Even/None)
  - Odd parity: Total 1's (data bits + parity bit) must be odd
  - Even parity: Total 1's (data bits + parity bit) must be even
  - None: No parity bit transmitted

- **Stop Bit(s)**
  - Line returns high for 1-2 bit periods
  - Marks end of transmission
  - Gives receiver time to process before next frame

## Communication Modes

1. **Simplex**

   - One-way communication only (TX → RX)

2. **Half-Duplex**

   - Two-way communication, but only one direction at a time

3. **Full-Duplex**
   - Simultaneous two-way communication (TX ↔ RX)

Below is an interactive demo in C showing serial data transmission:

## What's Here

- [`uart_demo.c`](./uart_demo.c) - Visualizes frame structure and voltage levels

## Quick Start

```bash
gcc uart_demo.c -o uart_demo
./uart_demo
```
