#include <gpio.h>
#include <common.h>

namespace libsoc {
    Gpio::Gpio(int pinNumber)
    {
        pin.reset(libsoc_gpio_request(pinNumber, gpio_mode::LS_GPIO_SHARED));
    }

    Gpio::~Gpio()
    {
        if (isInterrupt) libsoc_gpio_callback_interrupt_cancel(pin.get());
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

    Level Gpio::read()
    {
        gpio_level lev = libsoc_gpio_get_level(pin.get());
        switch (lev)
        {
        case gpio_level::HIGH:
            return Level::HIGH;
        case gpio_level::LOW:
            return Level::LOW;
        case gpio_level::LEVEL_ERROR:
            return Level::ERROR;
        default:
            return Level::ERROR;
        }
    }

    Result Gpio::setInterrupt(Edge edge, int (*callbackFunc)(void*), void* arg)
    {
        gpio_edge e;
        switch(edge)
        {
        case Edge::RISING:
            e = gpio_edge::RISING;
            break;
        case Edge::FALLING:
            e = gpio_edge::FALLING;
            break;
        case Edge::BOTH:
            e = gpio_edge::BOTH;
            break;
        case Edge::ERROR:
            e = gpio_edge::EDGE_ERROR;
            break;
        default:
            e = gpio_edge::EDGE_ERROR;
        }
        int res = libsoc_gpio_set_edge(pin.get(), e);
        if (res == EXIT_SUCCESS)
        {
            res = libsoc_gpio_callback_interrupt(pin.get(), callbackFunc, arg);
        }
        if (res == EXIT_SUCCESS)
        {
            isInterrupt = true;
        }
        return handleResult(res);
    }

    
}