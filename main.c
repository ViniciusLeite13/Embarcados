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
  
  File *log;
  
  // inicia o sensor
  rslt = bme280_init(&dev);
  rslt = stream_sensor_data_forced_mode(&dev);
    
  return 0;
}


// funcoes ----------------------

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr)
{
  struct identifier id;
  id = *((struct identifier *)intf_ptr);

  write(id.fd, &reg_addr, 1);
  read(id.fd, data, len);

  return 0;
}


void user_delay_us(uint32_t period, void *intf_ptr)
{
  usleep(period);
}


int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr)
{
  uint8_t *buf;
  struct identifier id;
  id = *((struct identifier *)intf_ptr);

  buf = malloc(len + 1);
  buf[0] = reg_addr;
  memcpy(buf + 1, data, len);
  
  if (write(id.fd, buf, len + 1) < (uint16_t)len)
  {
    return BME280_E_COMM_FAIL;
  }

  free(buf);

  return BME280_OK;
}


void print_sensor_data(struct bme280_data *comp_data)
{
  float temp, press, hum;

#ifdef BME280_FLOAT_ENABLE
  temp = comp_data->temperature;
  press = 0.01 * comp_data->pressure;
  hum = comp_data->humidity;
#else
#ifdef BME280_64BIT_ENABLE
  temp = 0.01f * comp_data->temperature;
  press = 0.0001f * comp_data->pressure;
  hum = 1.0f / 1024.0f * comp_data->humidity;
#else
  temp = 0.01f * comp_data->temperature;
  press = 0.01f * comp_data->pressure;
  hum = 1.0f / 1024.0f * comp_data->humidity;
#endif
#endif
  printf("%0.2lf deg C, %0.2lf hPa, %0.2lf%%\n", temp, press, hum);
}


int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev)
{
  int8_t rslt = BME280_OK;
  uint8_t settings_sel = 0;
  uint32_t req_delay;

  struct bme280_data comp_data;

  dev->settings.osr_h = BME280_OVERSAMPLING_1X;
  dev->settings.osr_p = BME280_OVERSAMPLING_16X;
  dev->settings.osr_t = BME280_OVERSAMPLING_2X;
  dev->settings.filter = BME280_FILTER_COEFF_16;

  settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

  rslt = bme280_set_sensor_settings(settings_sel, dev);
  if (rslt != BME280_OK)
  {
    fprintf(stderr, "Failed to set sensor settings (code %+d).", rslt);
    return rslt;
  }

  printf("Temperature, Pressure, Humidity\n");

  req_delay = bme280_cal_meas_delay(&dev->settings);

  // loop de transmissao dos dados do sensor
  while (1)
  {
    t = now();
  
    rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
    
    dev->delay_us(req_delay, dev->intf_ptr);
    rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);

    print_sensor_data(&comp_data);
            
    //Grava dados no cartao a cada 1 minuto
    if (second(t) == 0)
    {
      gravar(t, temp, press, hum);
    }
      
  }
  return rslt;
}







