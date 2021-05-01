#include <iostream>
#include <climits>
using namespace std;

#define GRID_SIZE 300

int power_level(int x, int y, int serial) {
  int rack_id = x + 10;
  int power = rack_id * y;
  power += serial;
  power *= rack_id;
  power = (power / 100) % 10;
  return power - 5;
}

// I could improve the time complexity, but I could also just wait the extra two minutes.
int max_power(int power_levels[GRID_SIZE][GRID_SIZE], int square_size, int &tlx, int &tly) {
  int max_power = INT_MIN;
  for (int x = 1; x <= GRID_SIZE - square_size - 1; ++x) {
    for (int y = 1; y <= GRID_SIZE - square_size - 1; ++y) {
      int power = 0;
      for (int dx = 0; dx < square_size; ++dx) {
        for (int dy = 0; dy < square_size; ++dy) {
          power += power_levels[x + dx - 1][y + dy - 1];
        }
      }
      if (power > max_power) {
        max_power = power;
        tlx = x;
        tly = y;
      }
    }
  }
  return max_power;
}

int main() {
  int serial;
  cin >> serial;

  int power_levels[GRID_SIZE][GRID_SIZE] = {};
  for (int x = 1; x <= GRID_SIZE; ++x) {
    for (int y = 1; y <= GRID_SIZE; ++y) {
      power_levels[x-1][y-1] = power_level(x, y, serial);
    }
  }

  int tlx, tly;
  cout << "Best: " << max_power(power_levels, 3, tlx, tly) << "@" << tlx << "," << tly << endl;

  int best = INT_MIN;
  int best_area, btlx, btly;
  for (int area = 1; area <= GRID_SIZE; ++area) {
    cout << area << endl;
    int power;
    if ((power = max_power(power_levels, area, tlx, tly)) > best) {
      best = power;
      best_area = area;
      btlx = tlx;
      btly = tly;
    }
  }
  cout << "Best: " << best << "@" << btlx << "," << btly << "," << best_area << endl;
}
