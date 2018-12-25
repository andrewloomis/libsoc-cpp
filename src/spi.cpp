#include <spi.h>
#include <common.h>

namespace libsoc {
    Spi::Spi(int bus, int cs)
    {
        mSpi.reset(libsoc_spi_init(bus, cs));
        libsoc_spi_set_mode(mSpi.get(), spi_mode::MODE_0);
        libsoc_spi_set_bits_per_word(mSpi.get(), spi_bpw::BITS_8);
    }

    Result Spi::frequency(int hertz)
    {
        int res = libsoc_spi_set_speed(mSpi.get(), hertz);
        return handleResult(res);
    }

    Spi::~Spi()
    {
        libsoc_spi_free(mSpi.get());
    }

    Result Spi::write(uint8_t* bytes, uint32_t len)
    {
        int res = libsoc_spi_write(mSpi.get(), bytes, len);
        return handleResult(res);
    }

    Result Spi::writeByte(uint8_t byte)
    {
        int res = libsoc_spi_write(mSpi.get(), &byte, 1);
        return handleResult(res);
    }

    Result Spi::read(uint8_t* buffer, uint32_t len)
    {
        int res = libsoc_spi_read(mSpi.get(), buffer, len);
        return handleResult(res);
    }

    uint8_t Spi::readByte()
    {
        uint8_t byte;
        libsoc_spi_read(mSpi.get(), &byte, 1);
        return byte;
    }

    Result Spi::transfer(uint8_t* txBuffer, uint8_t* rxBuffer, uint32_t len)
    {
        int res = libsoc_spi_rw(mSpi.get(), txBuffer, rxBuffer, len);
        return handleResult(res);
    }
}