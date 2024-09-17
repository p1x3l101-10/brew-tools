#include "homebrewTools.hpp"
#include <string>
#include <fstream>
#include <sys/resource.h>
#include <vector>
#include <utility>

using std::vector;
using std::pair;
using std::string;
using std::make_pair;
using homebrewTools::linkPairList;

linkPairList loadLinks (string filePath) {
    linkPairList links;
    {
        string line;
        string source;
        pair<string,string> link;
        string target;
        string delimiter = ":";
        std::ifstream linkFile(filePath);
        if (linkFile.is_open()) {
            while (std::getline(linkFile, line)) {
                // Extract pairs from file
                source = line.substr(0, line.find(delimiter));
                line.erase(0, line.find(delimiter) + delimiter.length());
                target = line;

                // Load it into the temporary pair
                link = make_pair(source, target);

                // Load the pair into the vector
                links.push_back(link);
            };
        };
    }
    return links;
}