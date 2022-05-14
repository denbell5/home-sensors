#include "tc74.h"
#include "i2c.h"

void tc74_init()
{
	i2c_start();
	i2c_send_addr(TC74_WRITE);
	i2c_send_byte(0x01);
	
	i2c_start();
	i2c_send_addr(TC74_READ);
	
	while(!(tc74_is_ready())) {
		_delay_ms(100);
	}
}

uint8_t tc74_is_ready()
{
	return i2c_readNak() & TC74_DATA_READY;
}

void tc74_write(uint8_t data)
{
	i2c_start();
	i2c_send_addr(TC74_WRITE); // tc74 sensor address
	i2c_send_byte(0x01); // send config register address
	i2c_send_byte(data); // send data
	i2c_stop();
}

uint8_t tc74_read()
{
	uint8_t status;
	status = i2c_start();
	status = i2c_send_addr(TC74_WRITE);
	status = i2c_send_byte(0x00);
	status = i2c_start();
	status = i2c_send_addr(TC74_READ);
	uint8_t data = i2c_readNak();
	i2c_stop();
	return data;
}