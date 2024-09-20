#include <string>
#include <utility>
#include "homebrewTools.hpp"
#include "linkAppsBin.hpp"

using std::pair;
using std::string;

using homebrewTools::linkPairList;

namespace constants = linkAppsBin::constants;

int main(int argc, char* argv[]){
    // Rotate old file
    homebrewTools::backupFile(constants::fileDb, constants::oldFileDb);

    // Generate current app list
    // Due to arch reasons, I need to load a sorted file, and bc I am also generating it I need to make it, sort it, then load it
    {
        // Get raw list
        linkPairList newLinks = linkAppsBin::generateAppLinks();
        // Save list to file
        linkAppsBin::dumpLinks(newLinks, constants::tmpFileDb);
        // Sort the file
        homebrewTools::sortFile(constants::tmpFileDb, constants::fileDb);
    }

    // Load links
    linkPairList newLinks = homebrewTools::loadLinks(constants::fileDb);
    linkPairList oldLinks = homebrewTools::loadLinks(constants::oldFileDb);

    // Find differences
    pair<linkPairList,linkPairList> differences = homebrewTools::changedLinks(oldLinks, newLinks);
    linkPairList pathsToLink = differences.first;
    linkPairList pathsToRemove = differences.second;

    // Operate
    homebrewTools::removeLinks(pathsToRemove);
    homebrewTools::createLinks(pathsToLink);

    // Exit
    return 0;
}