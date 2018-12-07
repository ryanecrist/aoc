/*

--- Day 6: Chronal Coordinates ---
The device on your wrist beeps several times, and once again you feel like you're falling.

"Situation critical," the device announces. "Destination indeterminate. Chronal interference detected. Please specify new target coordinates."

The device then produces a list of coordinates (your puzzle input). Are they places it thinks are safe or dangerous? It recommends you check manual page 729. The Elves did not give you a manual.

If they're dangerous, maybe you can minimize the danger by finding the coordinate that gives the largest distance from the other points.

Using only the Manhattan distance, determine the area around each coordinate by counting the number of integer X,Y locations that are closest to that coordinate (and aren't tied in distance to any other coordinate).

Your goal is to find the size of the largest area that isn't infinite. For example, consider the following list of coordinates:

1, 1
1, 6
8, 3
3, 4
5, 5
8, 9
If we name these coordinates A through F, we can draw them on a grid, putting 0,0 at the top left:

..........
.A........
..........
........C.
...D......
.....E....
.B........
..........
..........
........F.
This view is partial - the actual grid extends infinitely in all directions. Using the Manhattan distance, each location's closest coordinate can be determined, shown here in lowercase:

aaaaa.cccc
aAaaa.cccc
aaaddecccc
aadddeccCc
..dDdeeccc
bb.deEeecc
bBb.eeee..
bbb.eeefff
bbb.eeffff
bbb.ffffFf
Locations shown as . are equally far from two or more coordinates, and so they don't count as being closest to any.

In this example, the areas of coordinates A, B, C, and F are infinite - while not shown here, their areas extend forever outside the visible grid. However, the areas of coordinates D and E are finite: D is closest to 9 locations, and E is closest to 17 (both including the coordinate's location itself). Therefore, in this example, the size of the largest area is 17.

What is the size of the largest area that isn't infinite?

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctype.h>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  if (argc != 2) {
    cerr << "Usage: ./a.out <input_file>" << endl;
    exit(1);
  }

  string line; 
  ifstream inputFile(argv[1]);
  int minX = numeric_limits<int>::max();
  int maxX = numeric_limits<int>::min();
  int minY = numeric_limits<int>::max();
  int maxY = numeric_limits<int>::min();
  vector<int> xList;
  vector<int> yList;
  
  while (getline(inputFile, line)) {
    stringstream stream(line);
    char junk;
    int x, y;
    stream >> x >> junk >> y;
    xList.push_back(x);
    yList.push_back(y);
    minX = min(x, minX);
    minY = min(y, minY);
    maxX = max(x, maxX);
    maxY = max(y, maxY);
  }

  vector<int> areas(xList.size());

  for (int y = minY; y < maxY; ++y) {
    for (int x = minX; x < maxX; ++x) {

      int minDistance = numeric_limits<int>::max();
      int minIndex = -1;

      for (int i = 0; i < xList.size(); ++i) {

        int distance = abs(x - xList[i]) + abs(y - yList[i]);

        if (distance < minDistance) {
          minDistance = distance;
          minIndex = i;
        } else if (distance == minDistance) {
          minIndex = -1;
        }
      }

      if ((minIndex != -1) && 
          (xList[minIndex] > minX) && 
          (xList[minIndex] < maxX) &&
          (yList[minIndex] > minY) &&
          (yList[minIndex] < maxY)) {
        ++areas[minIndex];
      }
    }
  }

  cout << *max_element(areas.begin(), areas.end()) << endl;
}
