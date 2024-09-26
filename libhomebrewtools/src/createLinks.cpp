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
            switch (err.code().value()) {
                using std::errc;
                case (int) errc::file_exists: {
                    cerr << "WARN: File exists at: `" << target.string() << "`" << endl;
                    if (fs::is_symlink(target)){
                        cerr << "   File is already a symlink" << endl;
                        if (fs::read_symlink(target) == source) {
                            cerr << "   Link is correct, you make safely ignore this error" << endl;
                        } else {
                            cerr << "   Link exists, but does not point to the right location, manual resolution requierd" << endl
                                 << "   Please run `ln -sf '" << source.string() << "' '" << target.string() << "' to resolve" << endl;
                        }
                    } else {
                        cerr << "   File is not a symlink, manual resolution requierd" << endl
                             << "   Please run `ln -sf '" << source.string() << "' '" << target.string() << "' to resolve" << endl
                             << "   Make sure to move any important data before doing so" << endl;
                    }
                    break;
                }
                default: {
                    cerr << "Unknown filesystem error caught, manual resolution requied:" << endl << err.what() << endl;
                    cerr << "FS Error code \"" << err.code().message() << "\"" << endl;
                }
            }
        } catch (...) {
            cerr << "Unkown error caught in `libhomebrewtools/src/createLinks.cpp` dumping working variables..." << endl
                 << "   path source = " << source << endl
                 << "   path target = " << target << endl
                 << "Please report this error!" << endl;
            exit(255);
        }
    }
}