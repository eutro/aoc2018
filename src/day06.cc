#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <climits>
using namespace std;

#define MANHATTAN(a, b) (abs(a.first - b.first) + abs(a.second - b.second))

typedef pair<int, int> XY;

vector<XY> neighbours(XY xy) {
  return {{xy.first, xy.second + 1},
          {xy.first, xy.second - 1},
          {xy.first + 1, xy.second},
          {xy.first - 1, xy.second}};
}

int main() {
  vector<XY> coords;
  int x, y;
  int minx = INT_MAX, maxx = INT_MIN, miny = INT_MAX, maxy = INT_MIN;
  while (scanf("%d, %d", &x, &y) == 2) {
    coords.push_back({x, y});
    if (x < minx) minx = x;
    if (x > maxx) maxx = x;
    if (y < miny) miny = y;
    if (y > maxy) maxy = y;
  }

  map<int, set<XY>> closests;
  queue<pair<XY, int>> q;
  set<XY> seen;
  set<int> invalid;

  int key = 0;
  for (auto e : coords) {
    q.push({e, key++});
    seen.insert(e);
  }

  while (!q.empty()) {
    map<XY, int> next;
    while (!q.empty()) {
      auto pos = q.front();
      q.pop();
      closests[pos.second].insert(pos.first);
      for (auto neighbour : neighbours(pos.first)) {
        if (neighbour.first < minx ||
            neighbour.first > maxx ||
            neighbour.second < miny ||
            neighbour.second > maxy) {
          invalid.insert(pos.second);
          continue;
        }
        if (next.count(neighbour)) {
          if (next[neighbour] != pos.second) {
            next[neighbour] = -1;
          }
        } else {
          if (seen.count(neighbour)) continue;
          next[neighbour] = pos.second;
          seen.insert(neighbour);
        }
      }
    }
    for (auto e : next) {
      if (e.second != -1) q.push(e);
    }
  }

  int maxa = 0;
  for (auto e : closests) {
    // infinite
    if (invalid.count(e.first)) continue;
    if (e.second.size() > maxa) {
      maxa = e.second.size();
    }
  }
  cout << "Area: " << maxa << endl;

  int in_range = 0;
  for (int x = minx; x <= maxx; ++x) {
    for (int y = miny; y <= maxy; ++y) {
      int ranges = 0;
      XY pos = {x, y};
      for (XY loc : coords) {
        ranges += MANHATTAN(pos, loc);
      }
      if (ranges < 10000) in_range++;
    }
  }
  cout << "Area: " << in_range << endl;
}
