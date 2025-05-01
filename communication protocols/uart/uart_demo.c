#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HIGH "¯¯¯¯"
#define LOW "____"

typedef struct {
  uint32_t baud_rate;
  uint8_t parity; // 0=None, 1=Even, 2=Odd
  uint8_t stop_bits;
} UART_Config;

void print_binary_conversion(uint8_t data) {
  printf("\nData Conversion:\n");
  printf("Decimal: %u\n", data);
  printf("Hex: 0x%02X\n", data);

  printf("Binary (MSB first): ");
  for (int i = 7; i >= 0; i--) {
    printf("%d", (data >> i) & 1);
    if (i == 4)
      printf(" ");
  }

  printf("\nBinary (LSB first - UART order): ");
  for (int i = 0; i < 8; i++) {
    printf("%d", (data >> i) & 1);
    if (i == 3)
      printf(" ");
  }
  printf("\n");
}

void print_uart_frame(uint8_t data, const UART_Config *config) {
  printf("\nUART Frame Visualization:\n");
  printf("Idle\tStart\t");
  for (int i = 0; i < 8; i++)
    printf("D%d\t", i);
  if (config->parity)
    printf("Parity\t");
  for (int i = 0; i < config->stop_bits; i++)
    printf("Stop\t");
  printf("\n");

  // Idle state
  printf(HIGH "\t");

  // Start bit
  printf(LOW "\t");

  // Data bits
  for (int i = 0; i < 8; i++) {
    printf("%s\t", (data >> i) & 1 ? HIGH : LOW);
  }

  // Parity bit
  if (config->parity) {
    uint8_t ones = 0;
    for (int i = 0; i < 8; i++) {
      if ((data >> i) & 1)
        ones++;
    }
    uint8_t parity_bit = (config->parity == 1) ? (ones % 2) : !(ones % 2);
    printf("%s\t", parity_bit ? HIGH : LOW);
  }

  // Stop bits
  for (int i = 0; i < config->stop_bits; i++) {
    printf(HIGH "\t");
  }

  printf("\n");
}

void simulate_transmission(uint8_t data, const UART_Config *config) {
  printf("\nSimulating UART Transmission at %u baud:\n", config->baud_rate);
  unsigned int bit_duration = 1000000 / config->baud_rate;

  printf("TX Line: " HIGH " (Idle)\n");
  usleep(bit_duration * 2);

  printf("TX Line: " LOW " (Start bit)\n");
  usleep(bit_duration);

  for (int i = 0; i < 8; i++) {
    printf("TX Line: %s (Data bit %d - %d)\n",
           (data >> i) & 1 ? HIGH : LOW,
           i,
           (data >> i) & 1);
    usleep(bit_duration);
  }

  if (config->parity) {
    uint8_t ones = 0;
    for (int i = 0; i < 8; i++) {
      if ((data >> i) & 1)
        ones++;
    }
    uint8_t parity_bit = (config->parity == 1) ? (ones % 2) : !(ones % 2);
    printf("TX Line: %s (Parity bit - %d)\n",
           parity_bit ? HIGH : LOW,
           parity_bit);
    usleep(bit_duration);
  }

  for (int i = 0; i < config->stop_bits; i++) {
    printf("TX Line: " HIGH " (Stop bit %d)\n", i + 1);
    usleep(bit_duration);
  }

  printf("TX Line: " HIGH " (Return to idle)\n");
}

int main() {
  UART_Config config;
  uint8_t data;

  printf("UART Simulator (Simplex Mode)\n");
  printf("Data flows in one direction only: TX -> RX\n\n");

  // Baud rate selection
  printf("Select Baud Rate:\n");
  printf("1. 4800\n2. 9600\n3. 19200\n4. 57600\n5. 115200\n");
  printf("Choice: ");
  int choice;
  scanf("%d", &choice);

  switch (choice) {
  case 1:
    config.baud_rate = 4800;
    break;
  case 2:
    config.baud_rate = 9600;
    break;
  case 3:
    config.baud_rate = 19200;
    break;
  case 4:
    config.baud_rate = 57600;
    break;
  case 5:
    config.baud_rate = 115200;
    break;
  default:
    printf("Invalid choice. Using 9600 as default.\n");
    config.baud_rate = 9600;
  }

  printf("\nSelect Parity:\n");
  printf("0. None\n1. Even\n2. Odd\n");
  printf("Choice: ");
  scanf("%hhu", &config.parity);
  if (config.parity > 2) {
    printf("Invalid input. Using no parity as default.\n");
    config.parity = 0;
  }

  printf("\nEnter number of stop bits (1-2): ");
  scanf("%hhu", &config.stop_bits);
  if (config.stop_bits < 1 || config.stop_bits > 2) {
    printf("Invalid input. Using 1 stop bit as default.\n");
    config.stop_bits = 1;
  }

  printf("\nEnter data to transmit (0-255): ");
  scanf("%hhu", &data);

  print_binary_conversion(data);
  print_uart_frame(data, &config);
  simulate_transmission(data, &config);

  return 0;
}