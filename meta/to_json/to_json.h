#ifndef CPP_SERVICES_META_TO_JSON_H
#define CPP_SERVICES_META_TO_JSON_H


#include <type_traits>
#include "nlohmann/json.hpp"
#include "from_obj_to_is_list.h"
#include "from_properties_to_json.h"

namespace cpp_services
{

    namespace meta
    {

        /// \tparam T type that has no properties
        template<typename T, typename>
        struct to_json : public std::false_type
        {

            nlohmann::json operator()(const T &obj)
            {
                return cpp_services::meta::from_obj_to_is_list<T>{}.operator()(obj);
            }
        };

        ///
        /// \tparam T Specialization for typename = int
        template<typename T>
        struct to_json<T, decltype((void) T::properties, 0)> : std::true_type
        {

            nlohmann::json operator()(const T &obj)
            {
                return cpp_services::meta::from_properties_to_json<T>(obj);
            }
        };


        template<typename T>
        nlohmann::json to_json_as_any_list(const T &iterable_value)
        {
            nlohmann::json j{};

            for (const auto &elem : iterable_value)
            {
                j.push_back(cpp_services::meta::to_json<typename T::value_type>{}.operator()(elem));
            }

            return j;
        }

        template<typename T>
        struct to_json_as_any<boost::optional<T>>
        {

            nlohmann::json operator()(const boost::optional<T>& opt_value)
            {
                if(opt_value.is_initialized())
                    return cpp_services::meta::to_json< T>{}.operator()(opt_value.get());

                return {};
            }
        };


    }// namespace meta

}// namespace cpp_services


#endif// CPP_SERVICES_META_TO_JSON_H
