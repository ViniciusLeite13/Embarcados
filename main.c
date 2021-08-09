#ifdef __KERNEL__
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>

#include "funcoes.h"
#include "bme280.h"
#include "bme280_defs.h"


// struct --------------------

struct identifier
{
  uint8_t dev_addr;
  int8_t fd;
};

// funcoes -------------------

void user_delay_us(uint32_t period, void *intf_ptr);    // cria delay de (period) ms

void print_sensor_data(struct bme280_data *comp_data);  // printa dados de temperatura, umidade e pressão

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr);        // le os registradores do sensor pelo bus i2c

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr); // escreve nos registradores do sensor pelo bus i2c

int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev);  // le os dados de temperatura, umidade e pressão em modo forced


// main ----------------------

int main (int argc, char* argv[])
{
  struct bme280_dev dev;
  struct identifier id;
  
  int8_t rslt = BME280_OK;
  
  id.dev_addr = BME280_I2C_ADDR_PRIM;

  dev.intf = BME280_I2C_INTF;
  dev.read = user_i2c_read;
  dev.write = user_i2c_write;
  dev.delay_us = user_delay_us;
  dev.intf_ptr = &id;
  
  // inicia o sensor
  rslt = bme280_init(&dev);
  rslt = stream_sensor_data_forced_mode(&dev);
  
  
 
File *log;

  while(1)
  {
    t = now();
  
    //Grava dados no cartao a cada 1 minuto
    if (second(t) == 0)
    {
      gravar(t);
    }
 
  }
}

