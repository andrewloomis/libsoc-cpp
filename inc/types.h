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
        HIGH
    };

    enum class Edge
    {
        RISING,
        FALLING,
        BOTH
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