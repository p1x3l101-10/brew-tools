#include "homebrewTools.hpp"
#include "homebrewTools.hpp"
#include <ostream>
#include <utility>
#include <iostream>
#include <filesystem>

using std::cout;
using std::endl;
using std::cerr;

namespace fs = std::filesystem;
using fs::path;

using homebrewTools::linkPairList;

void homebrewTools::createLinks(linkPairList links) {
    for (const auto& link : links) {
        path source = link.first;
        path target = link.second;
        try {
            fs::create_directories(target.parent_path());
            fs::create_symlink(source, target);
            cout << "( Link Source: '" << source.string() << "' Target: '" << target.string() << "' )" << endl;
        } catch (fs::filesystem_error err) {
            cerr << "Error caught when linking files, manual resolution requied:" << endl << err.what() << endl;
        }
    }
}