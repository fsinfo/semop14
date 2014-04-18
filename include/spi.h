#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

void spi_init(void);
void spi_write_byte(uint8_t data);

#endif