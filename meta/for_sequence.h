#ifndef CPP_SERVICES_META_FOR_SEQUENCE_H
#define CPP_SERVICES_META_FOR_SEQUENCE_H

#include <utility>
#include <functional>

namespace cpp_services
{

    namespace meta
    {


        /// base case
        /// \tparam F
        /// \param f
        template<typename F>
        void first_level(F &&f)
        {
        }


        /// this simple deduces to: f(n), f(n+1), f(n+2)...
        /// \tparam F
        /// \tparam T type of integer sequence
        /// \tparam Tail type of integer sequence
        /// \param f function to call in body
        /// \param head
        /// \param tail
        template<typename F, typename T, typename... Tail>
        void first_level(F &&f, T head, Tail... tail)
        {
            f(head);
            first_level(f, tail...);
        }

        /// template for expanding the integer sequence in a series of function calls
        /// \tparam T type of integer sequence
        /// \tparam S type of integer sequence
        /// \tparam F function to pass at firs_level function
        /// \param f
        /// \return
        template<typename T, T... S, typename F>
        constexpr void for_sequence(std::integer_sequence<T, S...>, F &&f)
        {
            first_level(f, std::integral_constant<T, S>{}...);
        }

    }//namespace meta

}//namespace cpp_services

#endif// CPP_SERVICES_META_FOR_SEQUENCE_H
