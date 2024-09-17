#include <iostream>
#include <string>
#include "homebrewTools.hpp"

using std::string;
using std::cout;
using std::endl;

using homebrewTools::linkPairList;
using homebrewTools::linkPair;
using homebrewTools::loadLinks;
using homebrewTools::derefLinkPairList;

int main(int argc, char* argv[]) {
    string filePath = "./links.conf";
    linkPairList links = derefLinkPairList(loadLinks(filePath));
    for (const auto& link : links) {
        cout << "link: (Source: " << link.first << " , Target: " << link.second << " )" << endl;
    };
    return 0;
}