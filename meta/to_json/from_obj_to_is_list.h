#ifndef CPP_SERVICES_META_FROM_OBJ_TO_IS_LIST_H
#define CPP_SERVICES_META_FROM_OBJ_TO_IS_LIST_H


#include <type_traits>
#include "nlohmann/json.hpp"

namespace cpp_services
{

    namespace meta
    {

        ///template for converting a json value by the nlohmann json lib
        template<typename T>
        struct to_json_as_any
        {

            nlohmann::json operator()(const T &obj) { return obj; }

        };


        template<typename T>
        nlohmann::json to_json_as_any_list(const T &iterable_value);

        template<typename T>
        struct from_obj_to_is_list
        {

            static const bool value = false;

            nlohmann::json operator()(const T &obj)
            {
                return cpp_services::meta::to_json_as_any<T>{}.operator()(obj);
            }
        };

        /// template specialization for std::vector
        /// \tparam T
        /// \tparam U
        template<typename T, typename U>
        struct from_obj_to_is_list<std::vector<T, U>>
        {

            static const bool value = true;

            nlohmann::json operator()(const std::vector<T, U> &v_obj)
            {
                return cpp_services::meta::to_json_as_any_list<std::vector<T, U>>(v_obj);
            }
        };


    }// namespace meta

}// namespace cpp_services

#endif// CPP_SERVICES_META_FROM_OBJ_TO_IS_LIST_H
