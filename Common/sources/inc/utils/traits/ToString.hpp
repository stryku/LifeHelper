#pragma once

#include <utils/traits/traits.hpp>

namespace utils
{
    template <typename T, typename = std::enable_if_t<std::is_convertible<T, std::string>::value>>
    std::string toString(const T &value) const
    {
        return{ value };
    }

    template <typename T, typename = std::enable_if_t<CanCallToString<T>::value>>
    std::string toString(const T &value) const
    {
        return std::to_string(value);
    }

    template <typename T, typename = std::enable_if_t<std::is_same<T, bool>::value>>
    std::string toString(const T &value) const
    {
        return value ? "true" : "false";
    }

    template <typename T, typename = std::enable_if_t<hasToString<T, std::string()const>>::value>>
    std::string toString(const T &value) const
    {
        return value.toString();
    }
}