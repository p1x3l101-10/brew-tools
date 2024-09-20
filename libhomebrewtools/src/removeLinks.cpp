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

void homebrewTools::removeLinks(linkPairList links) {
    for (const auto& link : links) {
        path file = link.second;
        try {
            if (fs::remove(file)) {
                cout << "( Remove: '" << file.string() << "' )" << endl;
            } else {
                throw;
            }
        } catch (fs::filesystem_error err) {
            cerr << "Error caught when linking files, manual resolution requied:" << endl << err.what() << endl;
        } catch (...) {
            cerr << "Unknown error in 'libhomebrewtools/src/removeLinks.cpp', dumping working variables" << endl
                << "    path file = " << file.string() << endl
                << "Please report this error, continuing deletion..." << endl;
        }
    }
}