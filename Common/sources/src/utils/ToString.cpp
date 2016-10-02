#include "utils/ToString.hpp"

namespace utils
{
    std::string toString(bool value)
    {
        return value ? "true" : "false";
    }
}