#include "linkAppsBin.hpp"
#include "homebrewTools.hpp"
#include <string>
#include <fstream>

using homebrewTools::linkPairList;
using std::string;
using std::ofstream;
using std::endl;

void linkAppsBin::dumpLinks(linkPairList links, string filePath) {
    ofstream file (filePath);
    string source;
    string target;
    for (const auto& link : links) {
        source = link.first;
        target = link.second;
        file << source << ":" << target << endl;
    }
    file.close();
}