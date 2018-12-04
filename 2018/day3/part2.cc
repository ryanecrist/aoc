/*

--- Part Two ---
Amidst the chaos, you notice that exactly one claim doesn't overlap by even a single square inch of fabric with any other claim. If you can somehow draw attention to it, maybe the Elves will be able to make Santa's suit after all!

For example, in the claims above, only claim 3 is intact after all claims are made.

What is the ID of the only claim that doesn't overlap?

*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <unordered_set>

using namespace std;

int main(int argc, char **argv) {

  if (argc != 2) {
    cerr << "Usage: ./a.out <input_file>" << endl;
    exit(1);
  }

  string line;
  ifstream inputFile(argv[1]);
  map<string, vector<int>> pointIds;
  unordered_set<int> candidates;

  while (getline(inputFile, line)) {

    stringstream stream(line);
    char junk;
    int id, x, y, width, height;
    stream >> junk; // skip "#"
    stream >> id;
    stream >> junk; // skip "@"
    stream >> x;
    stream >> junk; // skip ","
    stream >> y;
    stream >> junk; // skip ":"
    stream >> width;
    stream >> junk; // skip "x"
    stream >> height;

    // add potential candidate
    candidates.insert(id);

    for (int i = x; i < x + width; ++i) {
      for (int j = y; j < y + height; ++j) {

        string key = to_string(i) + "," + to_string(j);
        pointIds[key].push_back(id);
        
        // remove any colliding IDs as candidates
        if (pointIds[key].size() > 1) {
          for (const int & id : pointIds[key]) {
            candidates.erase(id);
          }
        }
      }
    }
  }

  for (const int & candidate : candidates) {
    cout << candidate << endl;
  }
}