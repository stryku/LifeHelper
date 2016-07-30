#pragma once

#include <boost/variant.hpp>

namespace God
{
    namespace Subprograms
    {
        namespace Messages
        {
            template <typename Type, typename Args...>
            struct Message
            {
                Type type;
                boost::variant<Args...> variant;

                template <typename T>
                T& get() noexcept
                {
                    return variant.get<T>();
                }
            };
        }
    }
}