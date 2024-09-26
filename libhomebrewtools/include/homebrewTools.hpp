#ifndef HOMEBREW_TOOLS_HPP
#define HOMEBREW_TOOLS_HPP
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>

namespace homebrewTools {
    typedef std::pair<std::string, std::string> linkPair;
    typedef std::vector<homebrewTools::linkPair> linkPairList;
    std::string derefPrefix(std::string path);
    std::string unPrefix(std::string pathHeader, std::string prefixedPath);
    homebrewTools::linkPairList loadLinks(std::string filePath);
    homebrewTools::linkPairList derefLinkPairList(homebrewTools::linkPairList prefixedLinks);
    void fileBackup(std::string filePath);
    void linkFile(std::string source, std::string target);
    void removeLinks(homebrewTools::linkPairList links);
    void createLinks(homebrewTools::linkPairList links);
    void backupFile(std::string file, std::string backupPath);
    void sortFile(std::string filePath, std::string sortedPath);
    void checkLinks(homebrewTools::linkPairList links, bool correctErrors = false, bool keepGoing = false);

    /* Format for pair is as follows:
     * first: new
     * second: to remove
     */
    std::pair<homebrewTools::linkPairList,homebrewTools::linkPairList> changedLinks(homebrewTools::linkPairList oldLinks, homebrewTools::linkPairList newLinks);

    // Constants that are used in binaries
    namespace constants {
        const homebrewTools::linkPairList defaultEmpty = {{"", ""}};
        const std::string homebrewPrefix = std::getenv("HOMEBREW_PREFIX");
    };
};

#endif