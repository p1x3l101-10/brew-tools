#ifndef HOMEBREW_TOOLS_HPP
#define HOMEBREW_TOOLS_HPP
#include <string>
#include <vector>
#include <utility>

using std::string;

namespace homebrewTools {
    typedef std::pair<string, string> linkPair;
    typedef std::vector<linkPair> linkPairList;
    string derefPrefix(string path);
    string unPrefix(string pathHeader, string prefixedPath);
    linkPairList loadLinks(string filePath);
    linkPairList derefLinkPairList(linkPairList prefixedLinks);
};

#endif