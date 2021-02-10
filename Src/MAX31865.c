
#include <math.h>
#include <stdio.h>
#include "max31865.h"
#include "max31865Conf.h"
#if (_MAX31865_USE_FREERTOS == 1)
#include "cmsis_os.h"
#endif
//#########################################################################################################################
#define MAX31856_CONFIG_REG             0x00
#define MAX31856_CONFIG_BIAS            0x80
#define MAX31856_CONFIG_MODEAUTO        0x40
#define MAX31856_CONFIG_MODEOFF         0x00
#define MAX31856_CONFIG_1SHOT           0x20
#define MAX31856_CONFIG_3WIRE           0x10
#define MAX31856_CONFIG_24WIRE          0x00
#define MAX31856_CONFIG_FAULTSTAT       0x02
#define MAX31856_CONFIG_FILT50HZ        0x01
#define MAX31856_CONFIG_FILT60HZ        0x00

#define MAX31856_RTDMSB_REG             0x01
#define MAX31856_RTDLSB_REG             0x02
#define MAX31856_HFAULTMSB_REG          0x03
#define MAX31856_HFAULTLSB_REG          0x04
#define MAX31856_LFAULTMSB_REG          0x05
#define MAX31856_LFAULTLSB_REG          0x06
#define MAX31856_FAULTSTAT_REG          0x07


#define MAX31865_FAULT_HIGHTHRESH       0x80
#define MAX31865_FAULT_LOWTHRESH        0x40
#define MAX31865_FAULT_REFINLOW         0x20
#define MAX31865_FAULT_REFINHIGH        0x10
#define MAX31865_FAULT_RTDINLOW         0x08
#define MAX31865_FAULT_OVUV             0x04


#define RTD_A 3.9083e-3
#define RTD_B -5.775e-7
//#########################################################################################################################

//#########################################################################################################################
void Max31865_readRegisterN(struct max31865_dev *dev,uint8_t addr, uint8_t *buffer, uint8_t n)
{
  uint8_t tmp = 0xFF;
	addr &= 0x7F;
	HAL_GPIO_WritePin(dev->cs_gpio, dev->cs_pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(dev->spi,&addr, 1, 100);
	while (n--)
	{
    HAL_SPI_TransmitReceive(dev->spi, &tmp, buffer, 1, 100);
		buffer++;
	}
	HAL_GPIO_WritePin(dev->cs_gpio, dev->cs_pin, GPIO_PIN_SET);
}
//#########################################################################################################################
uint8_t Max31865_readRegister8(struct max31865_dev *dev,uint8_t addr)
{
  uint8_t ret = 0;
	Max31865_readRegisterN(dev, addr, &ret, 1);
	return ret;
}
//#########################################################################################################################
uint16_t Max31865_readRegister16(struct max31865_dev *dev,uint8_t addr)
{
	uint8_t buffer[2] = {0, 0};
	Max31865_readRegisterN(dev, addr, buffer, 2);
	uint16_t ret = buffer[0];
	ret <<= 8;
	ret |=  buffer[1];
	return ret;
}
//#########################################################################################################################
void Max31865_writeRegister8(struct max31865_dev *dev,uint8_t addr, uint8_t data)
{
	HAL_GPIO_WritePin(dev->cs_gpio, dev->cs_pin, GPIO_PIN_RESET);
  addr |= 0x80;
	HAL_SPI_Transmit(dev->spi,&addr, 1, 100);
	HAL_SPI_Transmit(dev->spi,&data, 1, 100);
	HAL_GPIO_WritePin(dev->cs_gpio, dev->cs_pin, GPIO_PIN_SET);
}
//#########################################################################################################################
uint8_t Max31865_readFault(struct max31865_dev *dev)
{
  return Max31865_readRegister8(dev, MAX31856_FAULTSTAT_REG);
}
//#########################################################################################################################
void Max31865_clearFault(struct max31865_dev *dev)
{
	uint8_t t = Max31865_readRegister8(dev, MAX31856_CONFIG_REG);
	t &= ~0x2C;
	t |= MAX31856_CONFIG_FAULTSTAT;
	Max31865_writeRegister8(dev, MAX31856_CONFIG_REG, t);
}
//#########################################################################################################################
void Max31865_enableBias(struct max31865_dev *dev, uint8_t enable)
{
	uint8_t t = Max31865_readRegister8(dev, MAX31856_CONFIG_REG);
	if (enable)
		t |= MAX31856_CONFIG_BIAS;
	else
		t &= ~MAX31856_CONFIG_BIAS;
	Max31865_writeRegister8(dev, MAX31856_CONFIG_REG, t);
}
//#########################################################################################################################
void Max31865_autoConvert(struct max31865_dev *dev, uint8_t enable)
{
	uint8_t t = Max31865_readRegister8(dev, MAX31856_CONFIG_REG);
	if (enable)
		t |= MAX31856_CONFIG_MODEAUTO;
	else
		t &= ~MAX31856_CONFIG_MODEAUTO;
	Max31865_writeRegister8(dev, MAX31856_CONFIG_REG, t);
}
//#########################################################################################################################
void Max31865_setWires(struct max31865_dev *dev, uint8_t numWires)
{
	uint8_t t = Max31865_readRegister8(dev, MAX31856_CONFIG_REG);
	if (numWires == 3)
		t |= MAX31856_CONFIG_3WIRE;
	else
		t &= ~MAX31856_CONFIG_3WIRE;
	Max31865_writeRegister8(dev, MAX31856_CONFIG_REG, t);
}
//#########################################################################################################################
void Max31865_setFilter(struct max31865_dev *dev, uint8_t filterHz)
{
	uint8_t t = Max31865_readRegister8(dev, MAX31856_CONFIG_REG);
	if (filterHz == 50)
		t |= MAX31856_CONFIG_FILT50HZ;
	else
		t &= ~MAX31856_CONFIG_FILT50HZ;
	Max31865_writeRegister8(dev, MAX31856_CONFIG_REG, t);
}
//#########################################################################################################################
uint16_t Max31865_readRTD (struct max31865_dev *dev)
{
	Max31865_clearFault(dev);
	Max31865_enableBias(dev, 1);
	HAL_Delay(10);
	uint8_t t = Max31865_readRegister8(dev, MAX31856_CONFIG_REG);
	t |= MAX31856_CONFIG_1SHOT;
	Max31865_writeRegister8(dev, MAX31856_CONFIG_REG, t);
	HAL_Delay(65);
	uint16_t rtd = Max31865_readRegister16(dev, MAX31856_RTDMSB_REG);
	printf("rtd: %u \n",rtd);
	rtd >>= 1;
	return rtd;
}
//#########################################################################################################################
//#########################################################################################################################
//#########################################################################################################################
void  Max31865_init(struct max31865_dev *dev, uint8_t  numwires, uint8_t filterHz)
{
  HAL_GPIO_WritePin(dev->cs_gpio,dev->cs_pin,GPIO_PIN_SET);
  HAL_Delay(100);
  Max31865_setWires(dev, numwires);
	Max31865_enableBias(dev, 0);
	Max31865_autoConvert(dev, 0);
	Max31865_clearFault(dev);
  Max31865_setFilter(dev, filterHz);
}
//#########################################################################################################################
uint8_t Max31865_readTempC(struct max31865_dev *dev,float *readTemp)
{
  uint8_t isOk = 0;
  float Z1, Z2, Z3, Z4, Rt, temp;
	Rt = Max31865_readRTD(dev);
	Rt /= 32768;
	Rt *= _MAX31865_RREF;
	Z1 = -RTD_A;
	Z2 = RTD_A * RTD_A - (4 * RTD_B);
	Z3 = (4 * RTD_B) / _MAX31865_RNOMINAL;
	Z4 = 2 * RTD_B;
	temp = Z2 + (Z3 * Rt);
	temp = (sqrtf(temp) + Z1) / Z4;

	if (temp >= 0)
	  {
		*readTemp = temp;
		if(Max31865_readFault(dev) == 0) isOk = 1;
		return isOk;
	  }
	Rt /= _MAX31865_RNOMINAL;
	Rt *= 100;
	float rpoly = Rt;
	temp = -242.02;
	temp += 2.2228 * rpoly;
	rpoly *= Rt;  // square
	temp += 2.5859e-3 * rpoly;
	rpoly *= Rt;  // ^3
	temp -= 4.8260e-6 * rpoly;
	rpoly *= Rt;  // ^4
	temp -= 2.8183e-8 * rpoly;
	rpoly *= Rt;  // ^5
	temp += 1.5243e-10 * rpoly;

  *readTemp = temp;
  if(Max31865_readFault(dev) == 0) isOk = 1;
  return isOk;
}
//#########################################################################################################################
uint8_t  Max31865_readTempF(struct max31865_dev *dev,float *readTemp)
{
  uint8_t isOk = Max31865_readTempC(dev,readTemp);
  *readTemp = (*readTemp * 9.0f / 5.0f) + 32.0f;
  return isOk;
}
//#########################################################################################################################
float Max31865_Filter(float	newInput, float	lastOutput, float efectiveFactor)
{
	return ((float)lastOutput*(1.0f-efectiveFactor)) + ((float)newInput*efectiveFactor) ;
}
//#########################################################################################################################
