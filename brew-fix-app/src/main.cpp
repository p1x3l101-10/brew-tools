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
  arguments::arguments args(argc, argv);

  if (args.map().contains("help")) {
    // Send a help message
    cout << args.vector().at(0) << ": Usage\n"
         << "\n"
         << "\t--app=/path/to/app.app" << "\t- The path to the application bundle." << "\n"
         << "\t--help" << "\t\t\t- This help message." << endl;
    return 0;
  }

  // Ensure we have the needed args
  if (! args.map().contains("app")) {
    cout << "Appbundle needed, see `--help`" << endl;
    return 1;
  }
  // Find app
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
  return 0;
}