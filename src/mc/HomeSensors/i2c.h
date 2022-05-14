/*
 * i2c.h
 *
 * Created: 5/13/2022 8:01:34 PM
 *  Author: Denis
 */ 

#include "main.h"

// ��������� ����
#define TWI_START                  0x08  // ����� ��� ���������
#define TWI_REP_START              0x10  // ��������� ����� ��� ���������
#define TWI_ARB_LOST               0x38  // ������ ����������, ���� ������

//���������������� ����
#define TWI_OK                0xff // ��� ������
#define TWSR_MASK          0xf8 // �����

// ��������� ���� �������� ����������� MTX
#define TWI_MTX_ADR_ACK            0x18  // ������� ����� ������-SLA+W � ��� ������� �����/������������� - ACK
#define TWI_MTX_ADR_NACK           0x20  // ������� ����� ������-SLA+W ��� ������������� - NACK
#define TWI_MTX_DATA_ACK           0x28  // ������� ���� � ��������� ������������� - ACK
#define TWI_MTX_DATA_NACK          0x30  // ������� ���� ��� ������������� - NACK

// ��������� ���� �������� ��������� MRX
#define TWI_MRX_ADR_ACK            0x40  // ������� ����� ������-SLA+R � ������� ����� ������������ - ACK
#define TWI_MRX_ADR_NACK           0x48  // S������� ����� ������-SLA+R ��� ������������ - NACK
#define TWI_MRX_DATA_ACK           0x50  // ������� ����  � ����������� ������������ �������� - ACK
#define TWI_MRX_DATA_NACK          0x58  // ������� ���� ��� ������������ �������� - NACK

void i2c_init(void); // ��������� ������� ���� �2�
void i2c_wait(void); // ��������
uint8_t i2c_start(void); // �����
void i2c_stop(void); // ����
uint8_t i2c_send_addr(uint8_t address); // �������� ������
uint8_t i2c_send_byte(uint8_t byte); // �������� �����
uint8_t i2c_read_byte(uint8_t *byte, uint8_t ack); // ������ �����. ack=0/1 - NACK/ACK

unsigned char i2c_readAck(void);
unsigned char i2c_readNak(void);