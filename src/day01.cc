#include <iostream>
#include <vector>
#include <set>

int main() {
  std::vector<int> ints;
  std::set<int> seen;
  int i, freq = 0;
  while (scanf("%d", &i) == 1) {
    ints.push_back(i);
    freq += i;
  }
  std::cout << "Resulting: " << freq << std::endl;

  freq = 0;
  while (true) {
    for (auto it = ints.begin(); it != ints.end(); ++it) {
      if (seen.count(freq)) {
        goto end;
      }
      seen.insert(freq);
      freq += *it;
    }
  }
 end:
  std::cout << "Repeated: " << freq << std::endl;
}
