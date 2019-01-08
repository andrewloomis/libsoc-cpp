#ifndef LIBSOC_CPP_SPI_H
#define LIBSOC_CPP_SPI_H

#include "types.h"
#include <inttypes.h>
#include <libsoc_spi.h>
#include <memory>

namespace libsoc {
    class Spi
    {
    public:
        Spi(int bus, int cs);
        ~Spi();
        Result frequency(int hertz);
        Result write(uint8_t* bytes, uint32_t len);
        Result writeByte(uint8_t byte);
        Result read(uint8_t* buffer, uint32_t len);
        uint8_t readByte();
        Result transfer(uint8_t* txBuffer, uint8_t* rxBuffer, uint32_t len);
    private:
        std::unique_ptr<spi> mSpi;
    };
}

#endif