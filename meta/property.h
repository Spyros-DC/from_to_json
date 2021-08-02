#ifndef CPP_SERVICES_META_PROPERTY_H
#define CPP_SERVICES_META_PROPERTY_H


namespace cpp_services
{

    namespace meta
    {

        ///template for implementing properties of a Class
        ///the conventions are p_member, name and Type (used in json_converter.h)
        ///this code is from "https://stackoverflow.com/questions/17549906/c-json-serialization"
        template<typename Class, typename T>
        struct propety_impl
        {
            constexpr propety_impl(T Class::*a_p_member, const char *a_name,
                                   bool is_optional = false)
                  : p_member{a_p_member}, name{a_name}, is_optional{is_optional}
            {
            }

            using Type = T;

            T Class::*p_member;
            const char *name;
            bool is_optional;
        };


        template<typename Class, typename T>
        constexpr auto property(T Class::*p_member, const char *name)
        {
            return propety_impl<Class, T>{p_member, name};
        }

    }//namespace meta

}//namespace cpp_services


#endif// CPP_SERVICES_META_PROPERTY_H
