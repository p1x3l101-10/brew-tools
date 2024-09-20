#include <string>
#include <utility>
#include "homebrewTools.hpp"
#include "linkFilesBin.hpp"

using std::string;
using std::pair;

using homebrewTools::linkPairList;
using homebrewTools::linkPair;
using homebrewTools::derefLinkPairList;

int main(int argc, char* argv[]) {
    // Rotate files, and save new
    homebrewTools::backupFile(linkFilesBin::constants::currentLinkFilePath, linkFilesBin::constants::oldLinkFilePath);
    homebrewTools::sortFile(linkFilesBin::constants::inputLinkFilePath, linkFilesBin::constants::currentLinkFilePath);

    // Load links
    linkPairList oldLinks = homebrewTools::loadLinks(linkFilesBin::constants::oldLinkFilePath);
    linkPairList newLinks = homebrewTools::loadLinks(linkFilesBin::constants::currentLinkFilePath);

    // Find differences
    pair<linkPairList,linkPairList> differences = homebrewTools::changedLinks(oldLinks, newLinks);
    linkPairList pathsToLink = differences.first;
    linkPairList pathsToRemove = differences.second;

    // Operate on files
    homebrewTools::removeLinks(derefLinkPairList(pathsToRemove));
    homebrewTools::createLinks(derefLinkPairList(pathsToLink));

    // Return
    return 0;
}