#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <utility>
using namespace std;

class Claim {
public:
  int id, left, top, width, height;
};

int main() {
  vector<Claim> claims;
  Claim claim;
  while (scanf("#%d @ %d,%d: %dx%d\n",
               &claim.id,
               &claim.left,
               &claim.top,
               &claim.width,
               &claim.height) == 5) {
    claims.push_back(claim);
  }
  map<pair<int, int>, int> claimed;
  set<pair<int, int>> overlap;
  set<int> overlapless;
  for (Claim claim : claims) {
    bool clean = true;
    for (int dx = 0; dx < claim.width; ++dx) {
      for (int dy = 0; dy < claim.height; ++dy) {
        pair<int, int> pos = make_pair(claim.left + dx, claim.top + dy);
        if (claimed.count(pos)) {
          overlap.insert(pos);
          clean = false;
          overlapless.erase(claimed[pos]);
        } else {
          claimed[pos] = claim.id;
        }
      }
    }
    if (clean) {
      overlapless.insert(claim.id);
    }
  }
  cout << "Overlap: " << overlap.size() << endl;
  if (overlapless.size() != 1) return 1;
  cout << "Clean: " << *overlapless.begin() << endl;
}
