#ifndef LINK_APPS_BIN_HPP
#define LINK_APPS_BIN_HPP

#include <string>
#include <vector>
#include "homebrewTools.hpp"

namespace linkAppsBin {
    std::string defaultEnv(std::string variable, std::string defaultValue);
    homebrewTools::linkPairList generateAppLinks(); // Find the current list of installed applications
    void dumpLinks(homebrewTools::linkPairList links); // Due to arcetecture reasons, I need to save my links to a file

    namespace constants {
        const std::string globalAppDir = linkAppsBin::defaultEnv("HOMEBREW_APPLICATIONS_DIRECTORY", homebrewTools::constants::homebrewPrefix + "/Applications");
        const std::vector<std::string> supportedAppSubdirs = { // Where to search for apps under the appdir
            "/",
            "/Sideloaded",
            "/WhiskyApps"
        };
    }
}

#endif