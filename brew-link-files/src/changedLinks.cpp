#include "linkFilesBin.hpp"
#include "homebrewTools.hpp"
#include <iterator>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>

using std::vector;
using std::pair;
using std::string;
using std::set_difference;
using std::sort;
using std::back_inserter;

using homebrewTools::linkPairList;

pair<linkPairList, linkPairList> linkFilesBin::changedLinks(linkPairList oldLinks, linkPairList newLinks) {
    sort(oldLinks.begin(), oldLinks.end());
    sort(newLinks.begin(),newLinks.end());

    pair<linkPairList,linkPairList> output;
    {
        {
            linkPairList linksToAdd;
            set_difference(newLinks.begin(),newLinks.end(),oldLinks.begin(),oldLinks.end(),back_inserter(linksToAdd));
            output.first = linksToAdd;
        }
        {
            linkPairList linksToRemove;
            set_difference(oldLinks.begin(), oldLinks.end(), newLinks.begin(), newLinks.end(), back_inserter(linksToRemove));
            output.second = linksToRemove;
        }
    }

    return output;
}