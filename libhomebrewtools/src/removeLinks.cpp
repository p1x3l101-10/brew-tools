#include "homebrewTools.hpp"
#include <ostream>
#include <utility>
#include <iostream>
#include <filesystem>

using std::cout;
using std::endl;

namespace filesystem = std::filesystem;
using filesystem::remove;
using filesystem::path;

using homebrewTools::linkPairList;

void homebrewTools::removeLinks(linkPairList links) {
    for (const auto& link : links) {
        path file = link.second;
        if (remove(file)) {
            cout << "( Remove: '" << file.string() << "' )" << endl;
        } else {
            cout << "!!! ( Failed to remove :'" << file.string() << "' )" << endl;
        }
    }
}