#ifndef CPP_SERVICES_META_FROM_PROPERTIES_TO_JSON_H
#define CPP_SERVICES_META_FROM_PROPERTIES_TO_JSON_H


#include "nlohmann/json.hpp"
#include "meta/for_sequence.h"


namespace cpp_services
{

    namespace meta
    {

        // forward declaration
        template<typename T, typename = int>
        struct to_json;

        template<typename T>
        nlohmann::json from_properties_to_json(const T &object)
        {
            nlohmann::json data;

            // We first get the number of properties
            constexpr auto number_of_properties = std::tuple_size<decltype(T::properties)>::value;

            // We iterate on the index sequence of size `nbProperties`
            for_sequence(std::make_index_sequence<number_of_properties>{}, [&](auto i) {
                // get the property
                constexpr auto property = std::get<i>(T::properties);

                // get the type of the property
                using Type = typename decltype(property)::Type;

                // set the value to the json field
                data[property.name] =
                        cpp_services::meta::to_json<Type>{}.operator()(object.*(property.p_member));
            });

            return data;
        }


    }//namespace meta

}// namespace cpp_services

#endif//CPP_SERVICES_META_FROM_PROPERTIES_TO_JSON_H
