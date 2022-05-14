#include "main.h"

// status code
#define TWI_START                  0x08  // start was sent
#define TWI_REP_START              0x10  // repeated start was sent
#define TWI_ARB_LOST               0x38  // bus is busy

// user code
#define TWI_OK                0xff // no errors
#define TWSR_MASK          0xf8 // mask

// MTX transmitter status codes
#define TWI_MTX_ADR_ACK            0x18  // write address -SLA+W transmitted and ACK received
#define TWI_MTX_ADR_NACK           0x20  // write address -SLA+W without ack - NACK
#define TWI_MTX_DATA_ACK           0x28  // byte transmitted and acknowledged - ACK
#define TWI_MTX_DATA_NACK          0x30  // byte transmitted without ack - NACK

// MRX receiver status codes
#define TWI_MRX_ADR_ACK            0x40  // read address -SLA+R transmitted and ACK received
#define TWI_MRX_ADR_NACK           0x48  // read address -SLA+R without ack - NACK
#define TWI_MRX_DATA_ACK           0x50  // byte received and ack sent to master
#define TWI_MRX_DATA_NACK          0x58  // byte received without ack - NACK

void i2c_init(void);
void i2c_wait(void);
uint8_t i2c_start(void);
void i2c_stop(void);
uint8_t i2c_send_addr(uint8_t address);
uint8_t i2c_send_byte(uint8_t byte);
uint8_t i2c_read_byte(uint8_t *byte, uint8_t ack);

unsigned char i2c_readAck(void);
unsigned char i2c_readNak(void);