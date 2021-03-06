#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

template <class T>
class LL {
public:
  LL<T> *next, *prev;
  T value;

  LL(T value) {
    this->value = value;
    prev = next = this;
  }

  LL(T value, LL<T> *prev, LL<T> *next) {
    this->value = value;
    this->prev = prev;
    prev->next = this;
    this->next = next;
    next->prev = this;
  }

  LL<T> *insert_after(T value) {
    return new LL<T>(value, this, next);
  }

  LL<T> *remove() {
    prev->next = next;
    next->prev = prev;
    LL<T> *tmp = next;
    delete this; // heck yeah
    return tmp;
  }
};

void play(int playerc, int last_marble, int &player, unsigned long long *scores, int &next_marble, LL<int> *&current) {
  while (next_marble <= last_marble) {
    if (next_marble % 23 == 0) {
      scores[player] += next_marble;
      for (int i = 0; i < 7; ++i) current = current->prev;
      scores[player] += current->value;
      current = current->remove();
    } else {
      current = current->next->insert_after(next_marble);
    }
    player = (player + 1) % playerc;
    next_marble++;
  }
}

int main() {
  LL<int> *tmp, *current, *root = new LL<int>(0);

  int playerc, last_marble;
  assert(scanf("%d players; last marble is worth %d points", &playerc, &last_marble) == 2);

  int player = 0;
  unsigned long long scores[playerc] = {};
  int next_marble = 1;
  current = root;
  play(playerc, last_marble, player, scores, next_marble, current);
  cout << "Winner: " << *max_element(scores, scores + playerc) << endl;
  last_marble *= 100;
  play(playerc, last_marble, player, scores, next_marble, current);
  cout << "Winner: " << *max_element(scores, scores + playerc) << endl;

  current = root->next;
  while (current != root) {
    tmp = current->next;
    delete current;
    current = tmp;
  }
  delete root;
}
