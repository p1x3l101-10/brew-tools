#include "homebrewTools.hpp"
#include <string>
#include <utility>

using std::string;
using std::pair;
using std::make_pair;
using homebrewTools::linkPair;
using homebrewTools::linkPairList;

linkPairList homebrewTools::derefLinkPairList(linkPairList prefixedLinks) {
    linkPairList realLinks;
    {
        linkPair link;
        linkPair realLink;
        string source;
        string realSource;
        string target;
        string realTarget;
        for (auto& link : prefixedLinks) {
            source = link.first;
            realSource = derefPrefix(source);
            target = link.second;
            realTarget = derefPrefix(target);
            realLink = make_pair(realSource, realTarget);
            realLinks.push_back(realLink);
        };
    }
    return realLinks;
}