#include <cstdlib>
#include <string>
#include "homebrewTools.hpp"

using std::string;

string homebrewTools::derefPrefix(string path) {
    string output;
    char prefix = path[1];
    switch ((int)prefix) {
        case (int)'r': // Root
            output = unPrefix("", path);
            break;
        case (int)'h': // Home
            output = unPrefix(getenv("HOME"), path);
            break;
        case (int)'p': // Homebrew Prefix
            output = unPrefix(getenv("HOMEBREW_PREFIX"), path);
            break;
        case (int)'a': // Application Support
            {
                string pathHeader = getenv("HOME");
                pathHeader += "/Library/Application Support";
                output = unPrefix(pathHeader, path);
            }
            break;

    };
    return output;
};