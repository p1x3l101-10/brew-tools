#include <string>
#include "homebrewTools.hpp"

using std::string;

string homebrewTools::unPrefix(string pathHeader, string prefixedPath) {
    string cleanPathlet = prefixedPath.substr(2);
    string realPath = pathHeader + cleanPathlet;
    return realPath;
};