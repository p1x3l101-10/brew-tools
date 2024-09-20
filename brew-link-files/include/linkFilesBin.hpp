#ifndef LINK_FILES_HPP
#define LINK_FILES_HPP

#include <string>
#include <utility>
#include <cstdlib>
#include  "homebrewTools.hpp"

namespace linkFilesBin {
    void fileBackup(std::string filePath);
    void linkFile(std::string source, std::string target);
    void removeLinks(homebrewTools::linkPairList links);
    void createLinks(homebrewTools::linkPairList links);
    void backupFile(std::string file, std::string backupPath);
    void sortFile(std::string filePath, std::string sortedPath);

    /* Format for pair is as follows:
     * first: new
     * second: to remove
     */
    std::pair<homebrewTools::linkPairList,homebrewTools::linkPairList> changedLinks(homebrewTools::linkPairList oldLinks, homebrewTools::linkPairList newLinks);

    // Constants that are used in the binary
    struct constants {
        const homebrewTools::linkPairList defaultEmpty = {{"", ""}};
        const std::string homebrewPrefix = std::getenv("HOMEBREW_PREFIX");
        const std::string inputLinkFilePath = homebrewPrefix + "/etc/homebrew/links.conf";
        const std::string currentLinkFilePath = homebrewPrefix + "/Library/.links.db";
        const std::string oldLinkFilePath = homebrewPrefix + "/Library/.links.db.old";
    };
}

#endif