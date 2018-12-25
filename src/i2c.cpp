#include <i2c.h>
#include <common.h>
#include <cstring>

namespace libsoc {
    I2c::I2c(uint8_t bus, uint8_t address)
    {
        mI2c.reset(libsoc_i2c_init(bus, address));
    }

    I2c::~I2c()
    {
        libsoc_i2c_free(mI2c.get());
    }

    Result I2c::write(uint8_t* bytes, uint16_t len)
    {
        int res = libsoc_i2c_write(mI2c.get(), bytes, len);
        return handleResult(res);
    }

    Result I2c::writeByte(uint8_t byte)
    {
        int res = libsoc_i2c_write(mI2c.get(), &byte, 1);
        return handleResult(res);
    }

    Result I2c::writeRegByte(uint8_t reg, uint8_t byte)
    {
        uint8_t tx[2] = {reg, byte};
        int res = libsoc_i2c_write(mI2c.get(), tx, 2);
        return handleResult(res);
    }

    Result I2c::writeRegBytes(uint8_t reg, uint8_t* bytes, uint16_t len)
    {
        uint8_t tx[len + 1];
        tx[0] = reg;
        memcpy(tx + 1, bytes, len);
        int res = libsoc_i2c_write(mI2c.get(), tx, len + 1);
        return handleResult(res);
    }

    Result I2c::read(uint8_t* buffer, uint16_t len)
    {
        int res = libsoc_i2c_read(mI2c.get(), buffer, len);
        return handleResult(res);
    }

    uint8_t I2c::readRegByte(uint8_t address)
    {
        write(&address, 1);
        uint8_t byte;
        libsoc_i2c_read(mI2c.get(), &byte, 1);
        return byte;
    }

    Result I2c::readRegBytes(uint8_t address, uint8_t* buffer, uint16_t len)
    {
        write(&address, 1);
        int res = libsoc_i2c_read(mI2c.get(), buffer, len);
        return handleResult(res);
    }
}