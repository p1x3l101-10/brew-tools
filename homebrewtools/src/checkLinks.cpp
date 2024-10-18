#include "homebrewTools.hpp"
#include <filesystem>
#include <ostream>
#include <stdexcept>
#include <string>
#include <iostream>

namespace fs =std::filesystem;

using std::cerr;
using std::cout;
using std::endl;
using homebrewTools::linkPairList;
using fs::path;
using std::string;
using std::pair;
typedef pair<path, path> plink;

string conflicDir () {
    string dirStr = std::getenv("HOME");
    dirStr += "/Link Conflicts";
    return dirStr;
}

enum cond {
    GOOD = 0,
    BAD_SOURCE,
    NOT_LINK,
    NOT_EXISTS,
    UNKOWN
};

void checkConflictDir () {
    path dir = conflicDir();
    if (fs::is_directory(dir)) {
    } else if (fs::exists(dir)) {
        throw std::runtime_error("Can't make conflict dir");
    } else {
        fs::create_directory(dir);
    }
}

void fixerUpper (plink link, int state) {
    path source = link.first;
    path target = link.second;
    cout << "Fixing...";
    switch (state) {
        case cond::BAD_SOURCE: {
            cout << "Changing target for: `" << target.string() << "`" << endl;
            fs::remove(target);
            homebrewTools::createLinks(homebrewTools::linkPairList {{source.string(), target.string()}});
            break;
        }
        case cond::NOT_LINK: {
            checkConflictDir();
            fs::rename(target, conflicDir() + target.filename().string());
            homebrewTools::createLinks(homebrewTools::linkPairList {{source.string(), target.string()}});
            cout << "Resolved conflict for: `" << target.filename().string() << "`" << endl;
            break;
        }
        case cond::NOT_EXISTS: {
            cout << "Creating link: `" << target.string() << "`" << endl;
            homebrewTools::createLinks(homebrewTools::linkPairList {{source.string(), target.string()}});
        }
    }
};

void homebrewTools::checkLinks(homebrewTools::linkPairList links, bool correctErrors, bool keepGoing) {
    path source;
    path target;
    for (const auto& link : links) {
        source = link.first;
        target = link.second;
        int state;
        // Detect errors
        if (fs::is_symlink(target) && (fs::read_symlink(target) == source)) {
            state = cond::GOOD;
        } else if (fs::is_symlink(target) && (fs::read_symlink(target) != source)) {
            state = cond::BAD_SOURCE;
        } else if (fs::exists(target)) {
            state = cond::NOT_LINK;
        } else if (! fs::exists(target)) {
            state = cond::NOT_EXISTS;
        } else {
            state = cond::UNKOWN;
        }

        // Print any errors that are found
        switch (state) {
            case cond::GOOD: {
                cout << "Link: `" << target.string() << "` is good";
                break;
            }
            case cond::BAD_SOURCE: {
                cerr << "Bad target for link `" << target.string() << "`" << endl
                     << "   Should be: `" << target.string() << "`" << endl
                     << "   Currently: `" << fs::read_symlink(target).string() << "`" << endl;
                break;
            }
            case cond::NOT_LINK: {
                cerr << "Target: `" << target.string() << "` is not a symlink!" << endl;
                break;
            }
            case cond::NOT_EXISTS: {
                cerr << "Target: `" << target.string() << "` does not exist!" << endl
                     << "   This could be from the parent directory not existing, or the link being removed" << endl;
                break;
            }
            case cond::UNKOWN:
            default: {
                // Basically, if I don't have a procedure of what to do, create an error
                string errorMsg = "Unknown state in `libhomebrewtools/src/checkLinks.cpp`";
                if (! keepGoing) {
                    // Unless told to keep going on error, throw said error
                    throw std::runtime_error(errorMsg);
                } else {
                    cerr << errorMsg;
                }
            }
        }

        // Run the fixerUpper if needed and requested
        if (correctErrors && ! (state == cond::GOOD || state == cond::UNKOWN)) {
            fixerUpper(link, state);
        }
    }
}