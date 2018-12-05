/*

--- Part Two ---
Strategy 2: Of all guards, which guard is most frequently asleep on the same minute?

In the example above, Guard #99 spent minute 45 asleep more than any other guard or minute - three times in total. (In all other cases, any guard spent any minute asleep at most twice.)

What is the ID of the guard you chose multiplied by the minute you chose? (In the above example, the answer would be 99 * 45 = 4455.)

*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char **argv) {

  if (argc != 2) {
    cerr << "Usage: ./a.out <input_file>" << endl;
    exit(1);
  }

  string line;
  ifstream inputFile(argv[1]);
  vector<string> lines;
  map<int, vector<int>> minutesAsleep;
  map<int, int> totalMinutesAsleep;

  while (getline(inputFile, line)) {
    lines.push_back(line);
  }

  sort(lines.begin(), lines.end());

  int currentGuardId;
  int currentMinute = 0;

  for (const auto & line : lines) {
    int colonIndex = line.find(':');
    int guardIndex = line.find('#');
    int asleepIndex = line.find("falls asleep");
    int awakeIndex = line.find("wakes up");

    int minute = stoi(line.substr(colonIndex + 1, 2));

    if (guardIndex != string::npos) {

      int idIndex = guardIndex + 1;
      currentGuardId = stoi(line.substr(idIndex, idIndex + (int) line.find(" begins")));

      if (totalMinutesAsleep.find(currentGuardId) == totalMinutesAsleep.end()) {
        totalMinutesAsleep[currentGuardId] = 0;
      }

      if (minutesAsleep.find(currentGuardId) == minutesAsleep.end()) {
          vector<int> mins(60);
          minutesAsleep[currentGuardId] = mins;
      }
      currentMinute = 0;

    } else if (asleepIndex != string::npos) {

      currentMinute = minute;

    } else if (awakeIndex != string::npos) {

      for (int i = currentMinute; i < minute; ++i) {
        ++minutesAsleep[currentGuardId][i];
        ++totalMinutesAsleep[currentGuardId];
      }
      currentMinute = minute;
    }
  }

  int guardId;
  int globalMaxMinute = -1;
  int globalMaxMinuteCount = 0;

  for (const auto & entry : minutesAsleep) {
    int maxMinute = max_element(entry.second.begin(), entry.second.end()) 
      - entry.second.begin();
    int maxMinuteCount = entry.second[maxMinute];
    if (maxMinuteCount > globalMaxMinuteCount) {
      guardId = entry.first;
      globalMaxMinute = maxMinute;
      globalMaxMinuteCount = maxMinuteCount;
    }
  }

  cout << guardId * globalMaxMinute << endl;
}
