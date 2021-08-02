#ifndef CPP_SERVICES_FROM_PROPERTIES_TO_OBJ_H
#define CPP_SERVICES_FROM_PROPERTIES_TO_OBJ_H


#include "nlohmann/json.hpp"
#include "meta/for_sequence.h"

namespace cpp_services
{

    namespace meta
    {

        /// forward declaration
        template<typename T, typename = int>
        struct from_json;

        /// template for implementing from json conversion to a struct/class
        /// based on properties of the struct/class from property.h
        template<typename T>
        T from_properties_to_obj(const nlohmann::json &data)
        {
            T object;

            // We first get the number of properties
            constexpr auto number_of_properties = std::tuple_size<decltype(T::properties)>::value;

            // We iterate on the index sequence of size `nbProperties`
            cpp_services::meta::for_sequence(
                    std::make_index_sequence<number_of_properties>{}, [&](auto i) {
                        // get the property
                        constexpr auto property = std::get<i>(T::properties);

                        // get the type of the property
                        using Type = typename decltype(property)::Type;

                        // set the value to the member
                        if (data.find(property.name) != data.end())
                        {

                            object.*(property.p_member) =
                                    cpp_services::meta::from_json<Type>{}.operator()(
                                            data[property.name]);

                            // throw exception if mandatory field
                        }
                        else if (!property.is_optional)
                        {

                            throw std::runtime_error{"field [ " + std::string{property.name} +
                                                     " ] not present in json for object [ " +
                                                     typeid(std::forward<T>(object)).name() +
                                                     " ] "};
                        }
                    });

            return object;
        }

    }// namespace meta

}// namespace cpp_services

#endif//CPP_SERVICES_FROM_PROPERTIES_TO_OBJ_H
