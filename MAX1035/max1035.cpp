
#include "max1035.h"

SPISettings SPI_write(1*1000*1000, MSBFIRST, SPI_MODE0);


MAX1035::MAX1035(uint8_t cs) :
  _cs(cs)
{
    
}

void MAX1035::init()
{
    // Set up pins
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);

    // Send a reset command
    write_command(RESET_A2D);
    delay(500);

    // Set ranges
    write_command(CH0 | UNIPOLAR_0_VREF); // channel 0 to single-ended, unipolar 0 to +Vref
    delay(50);
    write_command(CH1 | UNIPOLAR_0_VREF); // channel 1 to single-ended, unipolar 0 to +Vref
    delay(50);
    write_command(CH2 | UNIPOLAR_0_VREF); // channel 2 to single-ended, unipolar 0 to +Vref
    delay(50);
    write_command(CH3 | UNIPOLAR_0_VREF); // channel 3 to single-ended, unipolar 0 to +Vref
    delay(50);

    // Set mode control
    write_command(MODE_0);  // Mode 0, External Clock Mode
                            // Mode 1, External Aquisition Mode
                            // Mode 2, Internal Clock Mode

    // Wait for stuff to stabilise
    delay(250);

    return;
}

void MAX1035::update(uint8_t samples)
{
    uint32_t res_CH0 = 0;
    uint32_t res_CH1 = 0;
    uint32_t res_CH2 = 0;
    uint32_t res_CH3 = 0;

    // Read each channel the required number of times
    for (uint8_t ii = 0; ii < samples; ii++)
    {
        res_CH0 += (uint32_t)read_a2d(CH0);  // read channel 0
        res_CH1 += (uint32_t)read_a2d(CH1);  // read channel 1
        res_CH2 += (uint32_t)read_a2d(CH2);  // read channel 2
        res_CH3 += (uint32_t)read_a2d(CH3);  // read channel 3
    }

    // Take mean of output data
    _ch0 = (uint16_t)(res_CH0 / (uint32_t)samples);
    _ch1 = (uint16_t)(res_CH1 / (uint32_t)samples);
    _ch2 = (uint16_t)(res_CH2 / (uint32_t)samples);
    _ch3 = (uint16_t)(res_CH3 / (uint32_t)samples);
    return;
}

void MAX1035::write_command(uint8_t command)
{
    SPI.beginTransaction(SPI_write);
    digitalWrite(_cs, LOW);
    SPI.transfer(command);
    SPI.endTransaction();
    digitalWrite(_cs, HIGH);
}

uint16_t MAX1035::read_a2d(uint8_t command) 
{
  uint8_t  msb = 0;
  uint8_t  lsb = 0;
  uint16_t res = 0;

  SPI.beginTransaction(SPI_write);
  digitalWrite(_cs, LOW);
  SPI.transfer(command);
  SPI.transfer(0x00);
  msb = SPI.transfer(0x00);
  lsb = SPI.transfer(0x00);
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);

  // Compile bytes
  res = ((uint16_t)msb << 8) + (lsb);
  res = res >> 2;
  res = res & 0x3FFF;
  
  return res;
}

 uint16_t MAX1035::get_value(uint8_t channel)
 {
    // Returns the raw A2D value of the specified channel
    switch (channel) {
        case 0 :
            return (_ch0);
        case 1 :
            return (_ch1);
        case 2 :
            return (_ch2);
        case 3 :
            return (_ch3);
        default :
            return (0);
    }
 }
