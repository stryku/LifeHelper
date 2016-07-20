#pragma once

#include <utils/traits/traits.hpp>

#include <string>

namespace utils
{
    template <typename T>
    std::enable_if<std::is_convertible<T, std::string>::value, std::string>::type
        toString(const T &value)
    {
        return{ value };
    }

    template <typename T>
    std::enable_if_t<traits::CanCallToString<T>::value, std::string>::type
        toString(const T &value)
    {
        return std::to_string(value);
    }

    template <typename T>
    std::enable_if_t<traits::hasToString<T, std::string()const>::value, std::string>::type 
        toString(const T &value)
    {
        return value.toString();
    }

    std::string toString(bool value)
    {
        return value ? "true" : "false";
    }

}