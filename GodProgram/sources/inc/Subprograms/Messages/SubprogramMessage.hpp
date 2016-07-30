#pragma once

#include <utils/traits/traits.hpp>

#include <boost/variant.hpp>

#include <string>

namespace God
{
    namespace Subprograms
    {
        namespace Messages
        {
            template <typename Type, typename ...Args>
            struct Message
            {
                Type type;
                boost::variant<Args...> variant;

                template <typename T,
                          typename = std::enable_if_t<utils::traits::is_any_of<T, Args>::value>>
                T& get() noexcept
                {
                    return boost::get<T>(variant);
                }

                template <typename T,
                          typename = std::enable_if_t<utils::traits::is_any_of<T, Args>::value>>
                void set(const T &value) noexcept
                {
                    get<T>() = value;
                }
            };

            using Program2Message = Message<int, std::string>;
        }
    }
}