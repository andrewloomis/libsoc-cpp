#ifndef LIBSOC_CPP_GPIO_H
#define LIBSOC_CPP_GPIO_H

#include <libsoc_gpio.h>
#include <types.h>
#include <memory>

namespace libsoc {
    class Gpio
    {
    public:
        Gpio(int pinNumber);
        ~Gpio();
        Result setDirection(Direction direction);
        Direction getDirection();
        Result write(Level level);
        Level read();
        Result setInterrupt(Edge edge, int (*callbackFunc)(void*), void* arg);

    private:
        std::unique_ptr<gpio> pin;
        bool isInterrupt = false;
    };
}

#endif