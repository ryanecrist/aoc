/*

--- Part Two ---
As you're about to begin construction, four of the Elves offer to help. "The sun will set soon; it'll go faster if we work together." Now, you need to account for multiple people working on steps simultaneously. If multiple steps are available, workers should still begin them in alphabetical order.

Each step takes 60 seconds plus an amount corresponding to its letter: A=1, B=2, C=3, and so on. So, step A takes 60+1=61 seconds, while step Z takes 60+26=86 seconds. No time is required between steps.

To simplify things for the example, however, suppose you only have help from one Elf (a total of two workers) and that each step takes 60 fewer seconds (so that step A takes 1 second and step Z takes 26 seconds). Then, using the same instructions as above, this is how each second would be spent:

Second   Worker 1   Worker 2   Done
   0        C          .        
   1        C          .        
   2        C          .        
   3        A          F       C
   4        B          F       CA
   5        B          F       CA
   6        D          F       CAB
   7        D          F       CAB
   8        D          F       CAB
   9        D          .       CABF
  10        E          .       CABFD
  11        E          .       CABFD
  12        E          .       CABFD
  13        E          .       CABFD
  14        E          .       CABFD
  15        .          .       CABFDE
Each row represents one second of time. The Second column identifies how many seconds have passed as of the beginning of that second. Each worker column shows the step that worker is currently doing (or . if they are idle). The Done column shows completed steps.

Note that the order of the steps has changed; this is because steps now take time to finish and multiple workers can begin multiple steps simultaneously.

In this example, it would take 15 seconds for two workers to complete these steps.

With 5 workers and the 60+ second step durations described above, how long will it take to complete all of the steps?

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctype.h>
#include <map>
#include <vector>

using namespace std;

struct worker {
  char step;
  int seconds;
};

int main(int argc, char **argv) {

  if (argc != 2) {
    cerr << "Usage: ./a.out <input_file>" << endl;
    exit(1);
  }

  string line; 
  ifstream inputFile(argv[1]);
  map<char, vector<char>> tree;
  map<char, int> parentCounts;
  
  while (getline(inputFile, line)) {
    stringstream stream(line);
    string junk;
    char first, second;
    stream >> junk >> first >> junk >> junk >> junk >> junk >> junk >> second;

    if (tree.find(first) == tree.end()) {
      vector<char> children;
      tree[first] = children;
    }
    tree[first].push_back(second);

    if (parentCounts.find(first) == parentCounts.end()) {
      parentCounts[first] = 0;
    }

    if (parentCounts.find(second) == parentCounts.end()) {
      parentCounts[second] = 0;
    }
    ++parentCounts[second];
  }

  vector<char> availableSteps;
  for (const auto & node : parentCounts) {
    if (node.second == 0) {
      availableSteps.push_back(node.first);
    }
  }

  bool done = false;
  int totalSeconds = 0;
  vector<worker> workers(5);
  while (!done) {

    sort(availableSteps.rbegin(), availableSteps.rend());

    for (auto & worker : workers) {
      if ((worker.seconds == 0) && (availableSteps.size() > 0)) {
        char step = availableSteps.back();
        availableSteps.pop_back();
        worker.step = step;
        worker.seconds = step - '@' + 60;
      }
    }

    done = (availableSteps.size() == 0);
    for (auto & worker : workers) {

      done &= (worker.seconds == 0);
      if (worker.step != 0) {
        --worker.seconds;
      }
      
      if (worker.seconds == 0) {
        
        for (const char & child : tree[worker.step]) {
          
          --parentCounts[child];

          if (parentCounts[child] == 0) {
            availableSteps.push_back(child);
          }
        }

        worker.step = 0;
      }
    }

    if (!done) {
      ++totalSeconds;
    }
  }

  cout << totalSeconds << endl;
}
