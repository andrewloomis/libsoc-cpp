#include <gpio.h>

namespace libsoc {
    Gpio::Gpio(int pinNumber)
    {
        pin.reset(libsoc_gpio_request(pinNumber, gpio_mode::LS_GPIO_SHARED));
    }

    Gpio::~Gpio()
    {
        libsoc_gpio_free(pin.get());
    }

    Result Gpio::setDirection(Direction direction)
    {
        gpio_direction dir;
        switch(direction)
        {
        case Direction::INPUT:
            dir = gpio_direction::INPUT;
            break;
        case Direction::OUTPUT:
            dir = gpio_direction::OUTPUT;
            break;
        default:
            dir = gpio_direction::INPUT;
        }
        int res = libsoc_gpio_set_direction(pin.get(), dir);
        return handleResult(res);
    }

    Direction Gpio::getDirection()
    {
        gpio_direction dir = libsoc_gpio_get_direction(pin.get());
        switch(dir)
        {
        case gpio_direction::INPUT:
            return Direction::INPUT;
        case gpio_direction::OUTPUT:
            return Direction::OUTPUT;
        default:
            return Direction::ERROR;
        }
    }

    Result Gpio::write(Level level)
    {
        gpio_level lev;
        switch (level)
        {
        case Level::HIGH:
            lev = gpio_level::HIGH;
            break;
        case Level::LOW:
            lev = gpio_level::LOW;
            break;
        default:
            lev = gpio_level::LEVEL_ERROR;
        }
        int res = libsoc_gpio_set_level(pin.get(), lev);
        return handleResult(res);
    }

    

    Result Gpio::handleResult(int res)
    {
        switch (res)
        {
        case EXIT_SUCCESS:
            return Result::SUCCESS;
        case EXIT_FAILURE:
            return Result::FAILURE;
        default:
            return Result::FAILURE;
        }
    }
}