#ifndef _MAX31865_H
#define _MAX31865_H

/*
  Author:     Nima Askari
  WebSite:    http://www.github.com/NimaLTD
  Instagram:  http://instagram.com/github.NimaLTD
  Youtube:    https://www.youtube.com/channel/UCUhY7qY1klJm1d2kulr9ckw

  Version:    1.0.0


  Reversion History:

  (1.0.0)
  First Release.

*/

#ifdef __cplusplus
 extern "C" {
#endif

#include "gpio.h"
#include "spi.h"


#define PT1_INIT() \
  { \
    .cs_gpio = SPI2_CS_T1_GPIO_Port, \
    .cs_pin = SPI2_CS_T1_Pin, \
    .spi = &hspi2, \
  }

#define PT2_INIT() \
  { \
    .cs_gpio = SPI2_CS_T2_GPIO_Port, \
    .cs_pin = SPI2_CS_T2_Pin, \
    .spi = &hspi2, \
  }

#define PT3_INIT() \
  { \
    .cs_gpio = SPI2_CS_T3_GPIO_Port, \
    .cs_pin = SPI2_CS_T3_Pin, \
    .spi = &hspi2, \
  }

#define PT4_INIT() \
  { \
    .cs_gpio = SPI2_CS_T4_GPIO_Port, \
    .cs_pin = SPI2_CS_T4_Pin, \
    .spi = &hspi2, \
  }





//#########################################################################################################################
typedef struct max31865_dev
{
  GPIO_TypeDef      *cs_gpio;
  uint16_t          cs_pin;
  SPI_HandleTypeDef *spi;
} MAX31865;
//#########################################################################################################################
void  Max31865_init(struct max31865_dev *dev, uint8_t  numwires, uint8_t filterHz);
uint8_t  Max31865_readTempC(struct max31865_dev *dev, float *readTemp);
uint8_t  Max31865_readTempF(struct max31865_dev *dev, float *readTemp);
float Max31865_Filter(float	newInput, float	lastOutput, float efectiveFactor);
//#########################################################################################################################
#ifdef __cplusplus
}
#endif



#endif
