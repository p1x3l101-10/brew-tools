#include "linkAppsBin.hpp"
#include <filesystem>
#include <vector>
#include <cstdlib>
#include "homebrewTools.hpp"

namespace fs = std::filesystem;
namespace consts = linkAppsBin::constants;
using homebrewTools::linkPairList;
using homebrewTools::linkPair;
using fs::path;
using std::vector;
using std::string;
using std::getenv;

// base_name
std::string base_name(std::string const & path)
{
  return path.substr(path.find_last_of("/\\") + 1);
}

bool hasSuffix(string fullString, string suffix) {
    if (fullString.length() > suffix.length()) {
        return (0 == fullString.compare(fullString.length() - suffix.length(), suffix.length(), suffix));
    } else {
        return false;
    }
}

linkPairList linkAppsBin::generateAppLinks() {
    linkPairList output;
    string suffix = ".app";
    // Generate the paths to scan
    for (const auto& pathLet : consts::supportedAppSubdirs){
        path scanPath = consts::globalAppDir + pathLet;
        // Find all app bundles in the scanPath
        for (const auto& entry : fs::directory_iterator(scanPath)) {
            if (hasSuffix(entry.path().string(), suffix)) {
                // Generate output from found bundles
                path bundle = entry.path();
                string destination = getenv("HOME");
                destination += "/Applications" + pathLet;
                if (pathLet == "") { // Dont just splurge application links
                    destination += "/Homebrew";
                }
                destination += "/" + base_name(bundle.string());
                linkPair link = {bundle.string(), destination};
                output.push_back(link);
            }
        }
    }
    // Return
    return output;
}