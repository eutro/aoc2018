#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <cassert>
using namespace std;

#define LETTER_HEIGHT 8

class Light {
public:
  int x, y, dx, dy;

  void advance() {
    x += dx;
    y += dy;
  }

  void back() {
    x -= dx;
    y -= dy;
  }
};

void advance_lights(vector<Light> &lights) {
  for (auto it = lights.begin(); it != lights.end(); ++it) {
    it->advance();
  }
}

void back_lights(vector<Light> &lights) {
  for (auto it = lights.begin(); it != lights.end(); ++it) {
    it->back();
  }
}

void bounds(vector<Light> &lights, int &minx, int &maxx, int &miny, int &maxy) {
  minx = miny = INT_MAX;
  maxx = maxy = INT_MIN;
  for (Light light : lights) {
    if (light.x < minx) minx = light.x;
    if (light.x > maxx) maxx = light.x;
    if (light.y < miny) miny = light.y;
    if (light.y > maxy) maxy = light.y;
  }
}

void print_lights(vector<Light> &lights, int minx, int maxx, int miny, int maxy) {
  set<pair<int, int>> lit;
  for (Light l : lights) lit.insert({l.x, l.y});
  for (int y = miny; y <= maxy; ++y) {
    for (int x = minx; x <= maxx; ++x) {
      cout << (lit.count({x, y}) ? '#' : '.');
    }
    cout << endl;
  }
}

int main() {
  int x, y, dx, dy;
  vector<Light> lights;
  while (!cin.eof()) {
    cin.ignore(10);
    cin >> x;
    cin.ignore(1);
    cin >> y;
    cin.ignore(12);
    cin >> dx;
    cin.ignore(1);
    cin >> dy;
    cin.ignore(2);
    lights.push_back({x, y, dx, dy});
  }
  assert(lights.size() > 0);

  int time = 0;
  int min_height = INT_MAX;
  int minx, maxx, miny, maxy;
  while (true) {
    bounds(lights, minx, maxx, miny, maxy);
    if (min_height < maxy - miny) break;
    min_height = maxy - miny;
    ++time;
    advance_lights(lights);
  }

  back_lights(lights);
  bounds(lights, minx, maxx, miny, maxy);
  cout << "Message:" << endl;
  print_lights(lights, minx, maxx, miny, maxy);
  cout << "In: " << (time - 1) << " seconds" << endl;
}
