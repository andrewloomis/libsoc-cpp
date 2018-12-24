#ifndef LIBSOC_CPP_I2C_H
#define LIBSOC_CPP_I2C_H

#include <libsoc_i2c.h>
#include <types.h>
#include <inttypes.h>
#include <memory>

namespace libsoc {
    class I2c
    {
    public:
        I2c(uint8_t bus, uint8_t address);
        ~I2c();
        Result write(uint8_t* bytes, uint16_t len);
        Result writeRegByte(uint8_t reg, uint8_t byte);
        Result writeRegBytes(uint8_t reg, uint8_t* bytes, uint16_t len);
        Result read(uint8_t* buffer, uint16_t len);
        uint8_t readRegByte(uint8_t address);
        Result readRegBytes(uint8_t address, uint8_t* buffer, uint16_t len);
    
    private:
        std::unique_ptr<i2c> mI2c;
    };
}

#endif