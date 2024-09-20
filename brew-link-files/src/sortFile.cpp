#include "linkFilesBin.hpp"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using std::sort;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::getline;
using std::copy;
using std::ostream_iterator;

void linkFilesBin::sortFile(string filePath, string sortedPath) {
    ifstream inputFile(filePath);
    ofstream outputFile(sortedPath);

    if (inputFile.is_open() && outputFile.is_open()) {
        vector<string> lines;
        string line;

        while (getline(inputFile, line)) {
            lines.push_back(line);
        }

        sort(lines.begin(), lines.end());

        copy(lines.begin(), lines.end(), ostream_iterator<string>(outputFile, "\n"));
    }

    inputFile.close();
    outputFile.close();
}