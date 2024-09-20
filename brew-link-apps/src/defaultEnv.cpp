#include "linkAppsBin.hpp"
#include <string>
#include <cstdlib>

using std::string;
using std::getenv;

string linkAppsBin::defaultEnv(std::string variable, std::string defaultValue) {
    string envvar;
    if (getenv(variable.c_str())) {
        envvar = getenv(variable.c_str());
    } else {
        envvar = defaultValue;
    }
    return envvar;
}