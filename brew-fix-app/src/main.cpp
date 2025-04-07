#include "arguments.hpp"
#include "config.hpp"
#include <boost/process/v1/child.hpp>
#include <boost/process/v1/search_path.hpp>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
namespace fs = std::filesystem;
using fs::path;
using fs::absolute;
using fs::is_symlink;
using fs::read_symlink;
namespace bp = boost::process::v1;
using bp::child;
using bp::search_path;
using bp::ipstream;

int main(int argc, char** argv) {
  // Find app
  arguments::arguments args(argc, argv);
  path appBundle = args.map()["app"];

  // Fix refs to '~'
  if (appBundle.string().c_str()[0] == '~') {
    std::string filePath = appBundle.string();
    filePath.erase(0, 1);
    std::string homeDir = std::getenv("HOME");
    appBundle = homeDir + filePath;
  }
  // Fix any symlink refs
  if (is_symlink(appBundle)) {
    appBundle = read_symlink(appBundle);
  }
  // Resolve Path
  if (appBundle.is_relative()) {
    appBundle = absolute(appBundle);
  }

  // Run the fixup commands
  const vector<string> quarArgs = {
    "-r",
    "-d",
    QUARANTINE_ATTR,
    appBundle.string()
  };
  const vector<string> signArgs = {
    "--force",
    "--deep",
    "--sign",
    "-",
    appBundle.string()
  };
  child quarentine(search_path("xattr"), quarArgs);
  quarentine.wait();
  cout << "Removed attribute: " << QUARANTINE_ATTR << endl;
  child sign(search_path("codesign"), signArgs);
  sign.wait();
  cout << "Signed bundle" << endl;
}