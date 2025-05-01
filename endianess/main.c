#include <stdint.h>
#include <stdio.h>

int main() {
  // 32-bit data value
  uint32_t data = 0x12345678;

  // Array of 4 bytes to represent memory location
  uint8_t storage[4];
  uint8_t *storage_address = storage;

  printf("This is the data value we will be storing: 0x%x\n\r", data);

  printf("We will be storing the data in the following address locations\n");
  printf("\n_________\t_________\t_________\t_________\n");
  for (int i = 0; i < 4; i++) {
    printf("0x%x\t", (unsigned)(uintptr_t)storage_address + i);
  }

  int input;
  printf("\n\nWould you like to store this data value using Little Endian (LSB) (1) or Big Endian (MSB) (2)? ");
  scanf("%d", &input);

  while (input != 1 && input != 2) {
    printf("Please enter a valid input! ");
    scanf("%d", &input);
  }

  switch (input) {
    // Little Endian
  case 1:
    printf("Here is the data stored in Little Endian, with the least significant byte at the lowest memory location!!\n");
    storage_address[0] = (data >> 0) & 0xFF; // Extract LSB and store in lowest memory location
    storage_address[1] = (data >> 8) & 0xFF;
    storage_address[2] = (data >> 16) & 0xFF;
    storage_address[3] = (data >> 24) & 0xFF; // Extract MSB and store in highest memory location
    break;
    // Big Endian
  case 2:
    printf("Here is the data stored in Big Endian, with the most significant byte at the lowest memory location!!\n");
    storage_address[0] = (data >> 24) & 0xFF; // Extract MSB and store in lowest memory location
    storage_address[1] = (data >> 16) & 0xFF;
    storage_address[2] = (data >> 8) & 0xFF;
    storage_address[3] = (data >> 0) & 0xFF; // Extract LSB and store in highest memory location
    break;
  }

  printf("\n");
  for (int i = 0; i < 4; i++) {
    printf("0x%2X\t\t", storage_address[i]);
  }

  printf("\n_________\t_________\t_________\t_________\n");

  for (int i = 0; i < 4; i++) {
    printf("0x%x\t", (unsigned)(uintptr_t)storage_address + i);
  }
  printf("\n\r");

  return 0;
}
