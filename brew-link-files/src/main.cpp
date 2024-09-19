#include <string>
#include <utility>
#include "homebrewTools.hpp"
#include "linkFilesBin.hpp"

using std::string;
using std::pair;

using homebrewTools::linkPairList;
using homebrewTools::linkPair;
using homebrewTools::loadLinks;
using homebrewTools::derefLinkPairList;

using linkFilesBin::backupFile;
using linkFilesBin::sortFile;
using linkFilesBin::changedLinks;
using linkFilesBin::createLinks;
using linkFilesBin::removeLinks;

int main(int argc, char* argv[]) {
    const struct linkFilesBin::constants constants;
    // Rotate files, and save new
    backupFile(constants.currentLinkFilePath, constants.oldLinkFilePath);
    sortFile(constants.inputLinkFilePath, constants.currentLinkFilePath);

    // Load links
    linkPairList oldLinks = loadLinks(constants.oldLinkFilePath);
    linkPairList newLinks = loadLinks(constants.currentLinkFilePath);

    // Find differences
    pair<linkPairList,linkPairList> differences = changedLinks(oldLinks, newLinks);
    linkPairList pathsToLink = differences.first;
    linkPairList pathsToRemove = differences.second;

    // Operate on files
    removeLinks(derefLinkPairList(pathsToRemove));
    createLinks(derefLinkPairList(pathsToLink));

    // Return
    return 0;
}