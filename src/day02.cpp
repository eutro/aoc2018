#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main() {
  vector<string> lines;
  for (string line; getline(cin, line);) {
    lines.push_back(line);
  }

  unsigned int c2 = 0, c3 = 0;
  for (auto it = lines.begin(); it != lines.end(); ++it) {
    map<char, int> counts;
    for (auto c = it->begin(); c != it->end(); ++c) {
      counts[*c] += 1;
    }
    bool i2 = false, i3 = false;
    for (auto e = counts.begin(); e != counts.end(); ++e) {
      if (e->second == 2) {
        i2 = true;
      } else if (e->second == 3) {
        i3 = true;
      }
    }
    c2 += i2;
    c3 += i3;
  }
  cout << "Checksum: " << c2 * c3 << endl;

  for (auto slow = lines.begin(); slow != lines.end(); ++slow) {
    for (auto fast = slow + 1; fast != lines.end(); ++fast) {
      unsigned int difi, dif = 0, i = 0;
      auto a = slow->begin();
      auto b = fast->begin();
      while (a != slow->end() && b != fast->end()) {
        if (*a != *b) {
          ++dif;
          difi = i;
        }
        ++a;
        ++b;
        ++i;
      }
      if (dif == 1) {
        cout << "Common: " << slow->substr(0, difi) << &(*slow)[difi + 1] << endl;
        return 0;
      }
    }
  }
  return 1;
}
