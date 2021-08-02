#include <iostream>
#include "example_structs.h"
#include "meta/to_json/to_json.h"
#include "meta/from_json/from_json.h"

int main()
{

    foo foo_inst{3, "hi", {1,2,3}};

    bar bar_inst{ {foo_inst}, 17, 7};

    // function used by clients for serialization
    auto j1 = cpp_services::meta::to_json<bar>{}(bar_inst);

    std::cout << j1.dump() << "\n";

    // function used by clients for deserialization
    auto bar_inst_copy = cpp_services::meta::from_json<bar>{}(j1);

    return 0;
}
