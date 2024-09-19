#ifndef LINK_FILES_HPP
#define LINK_FILES_HPP

#include <string>
#include <utility>
#include <cstdlib>
#include  "homebrewTools.hpp"

using std::string;
using homebrewTools::linkPairList;
using std::pair;

namespace linkFilesBin {
    void fileBackup(string filePath);
    void linkFile(string source, string target);
    void removeLinks(linkPairList links);
    void createLinks(linkPairList links);
    void backupFile(string file, string backupPath);
    void sortFile(string filePath, string sortedPath);

    /* Format for pair is as follows:
     * first: new
     * second: to remove
     */
    pair<linkPairList,linkPairList> changedLinks(linkPairList oldLinks, linkPairList newLinks);

    // Constants that are used in the binary
    struct constants {
        const linkPairList defaultEmpty = {{"", ""}};
        const string homebrewPrefix = std::getenv("HOMEBREW_PREFIX");
        const string inputLinkFilePath = "./links.conf";
        const string currentLinkFilePath = "./links.db";
        const string oldLinkFilePath = "./links.db.old";
    };
}

#endif