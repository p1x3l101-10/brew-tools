#include "linkFilesBin.hpp"
#include "homebrewTools.hpp"
#include <ostream>
#include <string>
#include <utility>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

using homebrewTools::linkPairList;

void linkFilesBin::createLinks(linkPairList links) {
    for (const auto& link : links) {
        cout << "( Link Source: '" << link.first << "' Target: '" << link.second << "' )" << endl;
    }
}