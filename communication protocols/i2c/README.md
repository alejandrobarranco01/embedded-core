# I2C Communication Overview 🔗

**I2C** (Inter-Integrated Circuit) is a synchronous, master-slave communication protocol designed for short distance communication between integrated circuits. It supports bidirectional, half-duplex communication and can operate at multiple speeds. I2C uses only two wires, making it ideal for connecting multiple devices efficiently.

## Physical Connections

- **SCL (Serial Clock)**:

  - Clock signal generated by the master
  - Synchronizes data transmission

- **SDA (Serial Data)**:

  - Bidirectional data line for transmitting/receiving
  - Shared between all devices on the bus

- **Pull-Up Resistors**:
  - One resistor per line (SCL and SDA)
  - Pull both lines to a high voltage when idle
  - Enables open-drain design (devices pull lines low to signal)

## Required Settings

1. **Bus Speed Modes**:

   - **Standard Mode**: 100 kbps
   - **Fast Mode**: 400 kbps
   - **Fast Mode Plus**: 1 Mbps
   - **High-Speed Mode**: 3.4 Mbps

2. **Addressing**:

   - **7-bit addresses**: Most common (up to 127 devices)
   - **10-bit addresses**: Less common, supports more devices

3. **Data Frame Structure**:
   - **Address Frame**: 7/10-bit slave address + R/W bit
   - **Read/Write Bit**:
     - **0**: Master writes to slave
     - **1**: Master reads from slave
   - **ACK/NACK**:
     - Receiver sends ACK (0) after each byte
     - NACK (1) indicates failure/no acknowledgment

## Communication Process

1. **Idle State**:

   - Both SDA and SCL are pulled high.

2. **Start Condition**:

   - Master pulls SDA low while SCL is high.
   - Claims the bus and prevents other nodes from transmitting.

3. **Address Frame**:

   - Master sends 7/10-bit slave address (MSB first).
   - Followed by R/W bit to signal either a read or write operation.

4. **Slave Acknowledgment**:

   - Addressed slave pulls SDA low (ACK) in the next clock cycle.

5. **Data Transfer**:

   - **8-bit data** sent (MSB first), followed by ACK/NACK.
   - **SDA stability**: Data changes only when SCL is low.
   - Data is read/sampled by receiver when on the rising edge of SCL.

6. **Stop Condition**:
   - Master releases SDA to high after SCL goes high.
   - Ends communication and releases the bus.

## Communication Modes

1. **Single Master with Multiple Slaves**:

   - One master controls all communication.
   - Up to 127 slaves (7-bit addressing).

2. **Multi-Master Arbitration**:
   - Multiple masters can contend for bus control.
   - Arbitration ensures only one master wins (based on SDA data).

## Key Advantages

- **Minimal wiring**: Only two shared bus lines.
- **Multi-master support**: Flexible bus control.
- **Built-in addressing**: No separate chip-select lines.
- **Error checking**: ACK/NACK for each byte.

## Limitations

- **Speed**: Slower than SPI (due to half-duplex design).
- **Bus length**: Limited to short distances (board-level).
- **Pull-up dependency**: Resistor values affect performance.
- **Complexity**: Multi-master arbitration adds overhead.
