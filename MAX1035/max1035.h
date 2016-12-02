#include <Arduino.h>
#include <SPI.h>

#define CH0 0b10000000
#define CH1 0b10010000
#define CH2 0b10100000
#define CH3 0b10110000

#define MODE_0 0b10001000
#define MODE_1 0b10011000
#define MODE_2 0b10101000

#define RESET_A2D 0b11001000

#define UNIPOLAR_VREF_0 0b10000101
#define UNIPOLAR_0VREF2 0b10000011
#define UNIPOLAR_0_VREF 0b10000110


class MAX1035 {
    
    public :
    MAX1035(uint8_t cs);
    
    void init(void);
    void update(uint8_t samples);
    
    // Accessors
    uint16_t get_value(uint8_t channel);
    
    private :
    
    void     write_command(uint8_t command);
    uint16_t read_a2d(uint8_t command);
    
    uint8_t _cs;
    
    // A2D readings
    uint16_t _ch0 = 0;
    uint16_t _ch1 = 1;
    uint16_t _ch2 = 2;
    uint16_t _ch3 = 3;
    
};
