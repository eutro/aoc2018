#include <iostream>
#include <vector>
using namespace std;

#define OUT_LEN 10

void advance(vector<int> &recipes, vector<int> &elves) {
  int sum = 0;
  for (int elf : elves) {
    sum += recipes[elf];
  }

  for (char c : to_string(sum)) {
    recipes.push_back(c - '0');
  }

  for (int &elf : elves) {
    elf = (elf + recipes[elf] + 1) % recipes.size();
  }
}

bool check_at(vector<int> &recipes, string ns, int index) {
  for (int i = 0; i < ns.size(); ++i) {
    if (recipes[index + i] != (ns[i] - '0')) return false;
  }
  return true;
}

int main() {
  string ns; cin >> ns;
  int n = stoi(ns);

  vector<int> recipes = {3, 7};
  vector<int> elves = {0, 1};

  while (recipes.size() < n + OUT_LEN) {
    advance(recipes, elves);
  }

  cout << "Ten after: ";
  for (int i = 0; i < OUT_LEN; ++i) {
    cout << recipes[n + i];
  }
  cout << endl;

  int index = 0;
  while (!check_at(recipes, ns, index)) {
    ++index;
    if (index + ns.size() >= recipes.size()) {
      advance(recipes, elves);
    }
  }
  cout << "Follows: " << index << endl;
}
