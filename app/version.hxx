#ifndef VERSION_HXX
#define VERSION_HXX

#include <iostream>
#include <config.hpp>

namespace cmake::version {

static void print_version()
{
    std::cout << "Project Name: " << cmake::version::project_name << '\n'
              << "Project Version: " << cmake::version::project_version << std::endl;
}

}

#endif /* VERSION_HXX */
