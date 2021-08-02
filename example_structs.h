#ifndef FROM_TO_JSON_EXAMPLE_STRUCTS_H
#define FROM_TO_JSON_EXAMPLE_STRUCTS_H

#include <vector>
#include <string>
#include <boost/optional.hpp>
#include "meta/property.h"

struct foo{

    int x;
    std::string s;
    std::vector<int> v;

    // this is the required addition by the client
    constexpr static auto properties = std::make_tuple(
            cpp_services::meta::property(&foo::x, "x"),
            cpp_services::meta::property(&foo::s, "s"),
            cpp_services::meta::property(&foo::v, "v")
    );
};

struct bar{

    std::vector<foo> v;
    int x;
    boost::optional<int> opt_i;

    // this is the required addition by the client
    constexpr static auto properties = std::make_tuple(
            cpp_services::meta::property(&bar::v, "v"),
            cpp_services::meta::property(&bar::x, "x"),
            cpp_services::meta::property(&bar::opt_i,"optI" )
    );
};

#endif //FROM_TO_JSON_EXAMPLE_STRUCTS_H
