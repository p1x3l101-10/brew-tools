#include "homebrewTools.hpp"
#include "homebrewTools.hpp"
#include <ostream>
#include <utility>
#include <iostream>
#include <filesystem>
#include <sstream>

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
            std::stringstream errprint;
            switch (err.code().value()) {
                using std::errc;
                case (int) errc::file_exists: {
                    errprint << "WARN: File exists at: `" << target.string() << "`" << endl;
                    if (fs::is_symlink(target)){
                        if (fs::read_symlink(target) == source) {
                            errprint.str(""); // Wipe error message if link is already good
                        } else {
                            errprint << "   Link exists, but does not point to the right location, manual resolution requierd" << endl
                                     << "   Please run `ln -sf '" << source.string() << "' '" << target.string() << "'` to resolve" << endl;
                        }
                    } else {
                        errprint << "   File is not a symlink, manual resolution requierd" << endl
                                 << "   Please run `ln -sf '" << source.string() << "' '" << target.string() << "' to resolve" << endl
                                 << "   Make sure to move any important data before doing so" << endl;
                    }
                    break;
                }
                default: {
                    errprint << "Unknown filesystem error caught, manual resolution requied:" << endl << err.what() << endl;
                    errprint << "FS Error code \"" << err.code().message() << "\"" << endl;
                }
            }
            cerr << errprint.str();
            errprint.str(""); // Remove leftover data after printing the error
        } catch (...) {
            cerr << "Unkown error caught in `libhomebrewtools/src/createLinks.cpp` dumping working variables..." << endl
                 << "   path source = " << source << endl
                 << "   path target = " << target << endl
                 << "Please report this error!" << endl;
            exit(255);
        }
    }
}