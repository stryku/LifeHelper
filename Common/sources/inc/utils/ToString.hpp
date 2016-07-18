#pragma once

#include <utils/traits/traits.hpp>

#include <string>

namespace utils
{
    //template <typename T, typename = typename std::enable_if_t<std::is_convertible<T, std::string>::value>>
    template <typename T, typename = typename std::enable_if_t<std::is_convertible<T, std::string>::value>>
    std::string toString(const T &value)
    {
        return{ value };
    }

    template <class T, typename = void, typename = void, typename = std::enable_if_t<traits::hasToString<T, std::string()const>::value>>
    std::string toString(const T &value)
    {
        return value.toString();
    }

    //template <class T, typename = typename std::enable_if_t<traits::CanCallToString<T>::value>>
    template <class T, typename = void, typename = typename std::enable_if_t<traits::CanCallToString<T>::value>>
    std::string toString(const T &value)
    {
        return std::to_string(value);
    }

    std::string toString(bool value)
    {
        return value ? "true" : "false";
    }

}