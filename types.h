#ifndef LIBSOC_CPP_TYPES_H
#define LIBSOC_CPP_TYPES_H

namespace libsoc {
    enum class Direction
    {
        INPUT,
        OUTPUT,
        ERROR
    };

    enum class Level
    {
        LOW,
        HIGH,
        ERROR
    };

    enum class Edge
    {
        RISING,
        FALLING,
        BOTH,
        ERROR
    };

    enum class Result
    {
        INT_ERROR,
        INT_TRIGGERED,
        INT_TIMEOUT,
        SUCCESS,
        FAILURE
    };

}

#endif