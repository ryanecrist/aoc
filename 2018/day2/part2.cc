/*

--- Part Two ---
Confident that your list of box IDs is complete, you're ready to find the boxes full of prototype fabric.

The boxes will have IDs which differ by exactly one character at the same position in both strings. For example, given the following box IDs:

abcde
fghij
klmno
pqrst
fguij
axcye
wvxyz
The IDs abcde and axcye are close, but they differ by two characters (the second and fourth). However, the IDs fghij and fguij differ by exactly one character, the third (h and u). Those must be the correct boxes.

What letters are common between the two correct box IDs? (In the example above, this is found by removing the differing character from either ID, producing fgij.)

*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  if (argc != 2) {
    cerr << "Usage: ./a.out <input_file>" << endl;
    exit(1);
  }

  string line;
  ifstream inputFile(argv[1]);
  vector<string> previousLines;

  while (getline(inputFile, line)) {

    for (const auto & previousLine : previousLines) {

      int mismatchIndex = -1;
      int mismatchCount = 0;

      for (int i = 0; i < line.size(); ++i) {
        if (line[i] != previousLine[i]) {
          mismatchIndex = i;
          ++mismatchCount;
        }
      }

      if (mismatchCount == 1) {
        cout << line.erase(mismatchIndex, 1) << endl;
        exit(0);
      }
    }

    previousLines.push_back(line);
  }
}
