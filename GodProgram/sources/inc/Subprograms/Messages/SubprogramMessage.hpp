#pragma once

#include <utils/traits/traits.hpp>
#include <Subprograms/SignalType.hpp>

#include <boost/variant.hpp>

#include <string>

namespace God
{
    namespace Subprograms
    {
        namespace Messages
        {
            enum class MessageType
            {
                MODEL_CHANGE,
                MODEL_SIGNAL
            };

            template <typename Type, typename ...Args>
            struct InternalMessage
            {
                boost::variant<SignalType, Type> typeVariant;
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

                template <typename T,
                          typename = std::enable_if_t<std::is_same<T, SignalType>::value ||
                                                      std::is_same<T, Type>::value>>
                T getType() noexcept
                {
                    return boost::get<T>(typeVariant);
                }
            };

            template <typename Type, typename ...Args>
            struct Message
            {
                MessageType type;
                InternalMessage<Type, Args> internalMessage;
            };

            using Program2Message = Message<int, std::string>;
        }
    }
}