#pragma once

#include "utils/traits/traits.hpp"
#include "Communication/messages/SignalType.hpp"
#include "Communication/messages/MessageType.hpp"

#include "program2internals/communication/MessageType.hpp"

#include <boost/variant.hpp>

#include <string>



namespace God
{
    namespace Subprograms
    {
        namespace Messages
        {
            template <typename Type, typename ...Args>
            struct InternalMessage
            {
                using VariantType = boost::variant<Args...>;
                using BasicMessageType = Common::Communication::Messages::MessageType::Type;

                boost::variant<Common::Communication::SignalType::Type, Type> typeVariant;
                VariantType variant;

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
                          typename = std::enable_if_t<std::is_same<T, BasicMessageType>::value ||
                                                      std::is_same<T, Type>::value>>
                T getType() noexcept
                {
                    return boost::get<T>(typeVariant);
                }

                template <typename T, 
                          typename = std::enable_if_t<std::is_same<T, BasicMessageType>::value ||
                                                      std::is_same<T, Type>::value>>
                void setType(T type)
                {
                    boost::get<T>(typeVariant) = type;
                }
            };

            template <typename Type, typename ...Args>
            struct Message
            {
                using SubprogramMsgType = Type;

                Common::Communication::Messages::MessageType::Type type;
                InternalMessage<Type, Args...> internalMessage;
            };

            using SubprogramSignal = Message<Common::Communication::SignalType::Type>;


            using Program2Message = Message<P2::Communication::MessageType::Type, size_t>;
        }
    }
}