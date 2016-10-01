#pragma once

#include "Communication/messages/SignalType.hpp"
#include "Communication/messages/XmlMessageBuilder.hpp"

namespace Common
{
    namespace Communication
    {
        namespace Messages
        {
            class SignalFactory
            {
            private:
                template <typename T>
                using Elem = MessageBuilders::Xml::Element<T>;

                using Builder = MessageBuilders::Xml::Builder;

            public:
                template <typename ... Args>
                static std::string create(SignalType::Type type, Elem<Args> ... &args) 
                {
                    Builder builder;

                    const auto elements =
                    {
                        Elem{ "msg.type", "updateSum" },
                        Elem{ "msg.internals.type", SignalType::toString(type) }
                    };

                    builder.addElements(elements);

                    addCustomElements(builder, args...)

                    return builder.build();
                }

            private:
                template <typename Arg, typename ... Args>
                static void addCustomElements(Builder &builder, Elem<Arg> &elem, Elem<Args> ... &args)
                {
                    builder.addElement(elem);
                    addCustomElements(builder, args...);
                }

                static void addCustomElements(Builder&)
                {}
            };
        }
    }
}