#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <array>
using namespace std;

typedef long long ll;

map<char, int> dxs = {{'>', 1}, {'<', -1}, {'^',  0}, {'v', 0}};
map<char, int> dys = {{'>', 0}, {'<',  0}, {'^', -1}, {'v', 1}};
map<char, map<char, char>> redirects = {
  {'|', {{'v', 'v'}, {'^', '^'}}},
  {'-', {{'>', '>'}, {'<', '<'}}},
  {'/',
   {{'^', '>'}, {'>', '^'},
    {'v', '<'}, {'<', 'v'}}},
  {'\\',
   {{'^', '<'}, {'<', '^'},
    {'v', '>'}, {'>', 'v'}}},
};
#define TURN_CYCLE 3
map<char, array<char, TURN_CYCLE>> turns = {
  {'>', {'^', '>', 'v'}},
  {'v', {'>', 'v', '<'}},
  {'<', {'v', '<', '^'}},
  {'^', {'<', '^', '>'}},
};

class Cart {
public:
  ll x, y;
  char dir;
  int turnc;

  Cart(ll x, ll y, char dir) {
    this->x = x;
    this->y = y;
    this->dir = dir;
    turnc = 0;
  }

  bool operator<(const Cart &o) const {
    return make_pair(y, x) < make_pair(o.y, o.x);
  }

  void move(vector<string> &lines) {
    x += dxs[dir];
    y += dys[dir];
    char rail = lines[y][x];
    if (rail == '+') {
      dir = turns[dir][turnc];
      turnc = (turnc + 1) % TURN_CYCLE;
    } else {
      dir = redirects[rail].at(dir);
    }
  }
};

map<char, char> cart2rail = {
  {'v', '|'},
  {'^', '|'},
  {'>', '-'},
  {'<', '-'},
};

void show(vector<string> &lines, set<Cart> &carts) {
  for (ll y = 0; y < lines.size(); ++y) {
    for (ll x = 0; x < lines[y].size(); ++x) {
      auto er = carts.equal_range(Cart(x, y, '\0'));
      cout << (er.first == er.second ? lines[y][x] : er.first->dir);
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  set<Cart> carts;
  vector<string> lines;

  for (ll y = 0; true; ++y) {
    string line;
    getline(cin, line);
    if (!line.size()) break;
    for (ll x = 0; x < line.size(); ++x) {
      char *rail = &line[x];
      if (cart2rail.count(*rail)) {
        carts.insert(Cart(x, y, *rail));
        *rail = cart2rail[*rail];
      }
    }
    lines.push_back(line);
  }

  bool fcol = true;
  do {
    // show(lines, carts);
    set<Cart> newcarts = carts;
    for (Cart cart : carts) {
      if (!newcarts.count(cart)) continue;
      newcarts.erase(cart);
      cart.move(lines);
      if (newcarts.count(cart)) {
        if (fcol) {
          cout << "Collision: " << cart.x << "," << cart.y << endl;
          fcol = false;
        }
        newcarts.erase(cart);
      } else {
        newcarts.insert(cart);
      }
    }
    carts = newcarts;
  } while (carts.size() > 1);
  Cart last = *carts.begin();
  cout << "Last: " << last.x << "," << last.y << endl;
}
