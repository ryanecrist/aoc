/*

--- Part Two ---
Time to improve the polymer.

One of the unit types is causing problems; it's preventing the polymer from collapsing as much as it should. Your goal is to figure out which unit type is causing the most problems, remove all instances of it (regardless of polarity), fully react the remaining polymer, and measure its length.

For example, again using the polymer dabAcCaCBAcCcaDA from above:

Removing all A/a units produces dbcCCBcCcD. Fully reacting this polymer produces dbCBcD, which has length 6.
Removing all B/b units produces daAcCaCAcCcaDA. Fully reacting this polymer produces daCAcaDA, which has length 8.
Removing all C/c units produces dabAaBAaDA. Fully reacting this polymer produces daDA, which has length 4.
Removing all D/d units produces abAcCaCBAcCcaA. Fully reacting this polymer produces abCBAc, which has length 6.
In this example, removing all C/c units was best, producing the answer 4.

What is the length of the shortest polymer you can produce by removing all units of exactly one type and fully reacting the result?

*/


#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <vector>
#include <stack>

using namespace std;

int polymerLength(const string & input);

int main(int argc, char **argv) {

  if (argc != 2) {
    cerr << "Usage: ./a.out <input_file>" << endl;
    exit(1);
  }

  string input; 
  ifstream inputFile(argv[1]);
  getline(inputFile, input);

  if (input.size() < 2) {
    cout << input.size() << endl;
    exit(0);
  }

  int minLength = -1;

  for (int i = 'a'; i < 'a' + 26; ++i) {

    string newInput = input;
    newInput.erase(remove(newInput.begin(), newInput.end(), (char)i), newInput.end());
    newInput.erase(remove(newInput.begin(), newInput.end(), (char)toupper(i)), newInput.end());

    int length = polymerLength(newInput);

    if ((minLength == -1) || (length < minLength)) {
      minLength = length;
    }
  }

  cout << minLength << endl;
}

int polymerLength(const string & input) {

  string output;

  for (const char & c : input) {
    if (output.size() == 0) {
      output.push_back(c);
    } else if ((tolower(output.back()) == tolower(c)) && 
               ((islower(output.back()) && isupper(c)) || 
                (isupper(output.back()) && islower(c)))) {
      output.pop_back();
    } else {
      output.push_back(c);
    }
  }

  return output.size();
}