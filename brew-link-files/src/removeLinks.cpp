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

void linkFilesBin::removeLinks(linkPairList links) {
    for (const auto& link : links) {
        cout << "( Remove: '" << link.second << "' )" << endl;
    }
}