#pragma once

#include <type_traits>


namespace utils
{
    namespace traits
    {
        template<typename, typename T>
        struct hasToString {
            /*static_assert(
                std::integral_constant<T, false>::value,
                "Second template parameter needs to be of function type.");*/
            static constexpr bool value = false;
        };

        template<typename C, typename Ret, typename... Args>
        struct hasToString<C, Ret(Args...)> {
        private:
            template<typename T>
            static constexpr auto check(T*) -> typename std::is_same<decltype(std::declval<T>().toString(std::declval<Args>()...)),
                                                                     Ret>::type;

            template<typename>
            static constexpr std::false_type check(...);

            typedef decltype(check<C>(0)) type;

        public:
            static constexpr bool value = type::value;
        };

        template <typename T>
        struct canCallStdToString
        {
            static constexpr bool value = !std::is_same<T, bool>::value &&
                                          (std::is_integral<T>::value || 
                                           std::is_unsigned<T>::value || 
                                           std::is_floating_point<T>::value);
        };
    }
}