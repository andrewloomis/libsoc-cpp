#include <common.h>
#include <libsoc_gpio.h>

namespace libsoc {
    Result handleResult(int res)
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