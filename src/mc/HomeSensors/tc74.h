#include "main.h"

#define TC74_READ  0b10011011
#define TC74_WRITE 0b10011010
#define TC74_DATA_READY 0b01000000

void tc74_write(uint8_t data);
uint8_t tc74_read();
uint8_t tc74_is_ready();
void tc74_init();