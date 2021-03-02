#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool destroys(char a, char b) {
  return abs(a - b) == 'a' - 'A';
}

vector<char> reduce(string &line, char filter) {
  vector<char> polymer;
  polymer.push_back(line[0]);
  for (size_t i = 1; i < line.size(); ++i) {
    char c = line[i];
    if (destroys(polymer.back(), c)) {
      polymer.pop_back();
    } else if (c != filter && !destroys(c, filter)) {
      polymer.push_back(c);
    }
  }
  return polymer;
}

int main() {
  string line;
  getline(cin, line);
  cout << reduce(line, '\0').size() << endl;
  vector<int> lengths;
  for (char c : "abcdefghijklmnopqrstuvwxyz") lengths.push_back(reduce(line, c).size());
  cout << *min_element(lengths.begin(), lengths.end()) << endl;
}
