#ifndef LINK_FILES_HPP
#define LINK_FILES_HPP

#include <string>
#include  "homebrewTools.hpp"

namespace linkFilesBin {
    namespace constants {
        const std::string inputLinkFilePath = homebrewTools::constants::homebrewPrefix + "/etc/homebrew/links.conf";
        const std::string currentLinkFilePath = homebrewTools::constants::homebrewPrefix + "/Library/.links.db";
        const std::string oldLinkFilePath = homebrewTools::constants::homebrewPrefix + "/Library/.links.db.old";
    };
}

#endif