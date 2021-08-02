#ifndef CPP_SERVICES_FROM_JSON_H
#define CPP_SERVICES_FROM_JSON_H

#include "from_json_to_is_list.h"
#include "from_properties_to_obj.h"
#include "nlohmann/json.hpp"
#include <type_traits>

namespace cpp_services
{

    namespace meta
    {

        /// \tparam T type that has no properties
        template<typename T, typename>
        struct from_json : public std::false_type
        {

            T operator()(const nlohmann::json &j)
            {
                return cpp_services::meta::from_json_to_is_list<T>{}.operator()(j);
            }
        };

        ///
        /// partial template specialization
        /// \tparam T type that has properties
        template<typename T>
        struct from_json<T, decltype((void) T::properties, 0)> : std::true_type
        {

            T operator()(const nlohmann::json &j)
            {
                return cpp_services::meta::from_properties_to_obj<T>(j);
            }
        };

        ///
        /// \tparam T
        /// \param value
        /// \return iterable type from json array
        template<typename T>
        T as_any_list(const nlohmann::json &value)
        {
            T res{};

            for (const auto &json_elem : value)
            {
                res.push_back(cpp_services::meta::from_json<typename T::value_type>{}.operator()(
                        json_elem));
            }

            return res;
        }

        //partial specialization
        template<typename T>
        struct as_any< boost::optional<T> >{

            boost::optional<T> operator()(const nlohmann::json& value)
            {
                return cpp_services::meta::from_json<T>{}.operator()(value);
            }
        };

    }// namespace meta

}// namespace cpp_services

#endif// CPP_SERVICES_FROM_JSON_H
