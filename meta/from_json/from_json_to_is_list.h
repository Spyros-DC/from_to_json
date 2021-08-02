#ifndef CPP_SERVICES_META_FROM_JSON_TO_IS_LIST_H
#define CPP_SERVICES_META_FROM_JSON_TO_IS_LIST_H


#include <type_traits>
#include "nlohmann/json.hpp"
#include <boost/optional.hpp>

namespace cpp_services
{

    namespace meta
    {

        ///template for converting a json value by the nlohman json lib
        template<typename T>
        struct as_any
        {

            T operator()(const nlohmann::json &value) { return value.get<T>(); }
        };

        //forward declaration
        template<typename T>
        T as_any_list(const nlohmann::json &value);

        ///
        /// \tparam T type that is not a list of elements
        template<typename T>
        struct from_json_to_is_list
        {

            static const bool value = false;

            T operator()(const nlohmann::json& j) { return cpp_services::meta::as_any<T>{}.operator()(j);}
        };

        /// template specialization for std::vector as a list of elements
        /// \tparam T
        /// \tparam U
        template<typename T, typename U>
        struct from_json_to_is_list<std::vector<T, U>>
        {

            static const bool value = true;

            std::vector<T, U> operator()(const nlohmann::json &j)
            {
                return cpp_services::meta::as_any_list<std::vector<T, U>>(j);
            }
        };


    }// namespace meta

}// namespace cpp_services

#endif// CPP_SERVICES_META_FROM_JSON_TO_IS_LIST_H
