#include "linkFilesBin.hpp"
#include "homebrewTools.hpp"
#include <ostream>
#include <utility>
#include <iostream>
#include <filesystem>

using std::cout;
using std::endl;

namespace filesystem = std::filesystem;
using filesystem::create_symlink;
using filesystem::create_directories;
using filesystem::path;

using homebrewTools::linkPairList;

void linkFilesBin::createLinks(linkPairList links) {
    for (const auto& link : links) {
        path source = link.first;
        path target = link.second;
        create_directories(target.parent_path());
        create_symlink(source, target);
        cout << "( Link Source: '" << source.string() << "' Target: '" << target.string() << "' )" << endl;
    }
}