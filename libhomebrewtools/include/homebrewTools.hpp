#ifndef HOMEBREW_TOOLS_HPP
#define HOMEBREW_TOOLS_HPP
#include <string>
#include <vector>
#include <utility>

namespace homebrewTools {
    typedef std::pair<std::string, std::string> linkPair;
    typedef std::vector<linkPair> linkPairList;
    std::string derefPrefix(std::string path);
    std::string unPrefix(std::string pathHeader, std::string prefixedPath);
    linkPairList loadLinks(std::string filePath);
    linkPairList derefLinkPairList(linkPairList prefixedLinks);
};

#endif