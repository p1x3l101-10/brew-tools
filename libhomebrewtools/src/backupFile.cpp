#include "homebrewTools.hpp"
#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

void homebrewTools::backupFile(string file, string backupPath) {
    ifstream input(file, ios::binary);
    ofstream output(backupPath, ios::binary);

    if (input.good()) {
        if (output.good()) {
            output << input.rdbuf();
        }
    }

    input.close();
    output.close();
}