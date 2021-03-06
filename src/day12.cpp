#include <iostream>
#include <map>
using namespace std;

#define GENERATIONS 20
#define GENERATIONS_WINDUP 100
#define GENERATIONS_BIG 50000000000
#define BUFSZ 100
#define OFFSET 25
#define CSET(c) (c == '#')
#define BYTEREF(buf, bit) (buf[(OFFSET * 8 + (bit)) / 8])
#define SETBIT(buf, bit, v) (BYTEREF(buf, bit) ^= (-(unsigned char)!!(v) ^ BYTEREF(buf, bit)) & (1 << ((8 + (bit)) % 8)))
#define GETBIT(buf, bit) ((BYTEREF(buf, bit) & (1 << ((8 + (bit)) % 8))) != 0)
#define REF5(buf, bit) (GETBIT(buf, bit - 2) << 4 | \
                        GETBIT(buf, bit - 1) << 3 | \
                        GETBIT(buf, bit - 0) << 2 | \
                        GETBIT(buf, bit + 1) << 1 | \
                        GETBIT(buf, bit + 2) << 0)
#define SWAP(x, y) auto __tmp = x; x = y; y = __tmp;

void printrange(unsigned char *buf, int min, int max) {
  for (int i = min; i <= max; ++i) {
    cout << (GETBIT(buf, i) ? '#' : '.');
  }
  cout << endl;
}

void advancef(unsigned char *b, unsigned char *tb, int &minset, int &maxset, map<unsigned char, bool> &rules) {
  for (int bit = minset; bit <= maxset; ++bit) {
      SETBIT(tb, bit, rules[REF5(b, bit)]);
    }
  if (GETBIT(tb, minset)) --minset;
  if (GETBIT(tb, maxset)) ++maxset;
}

int sumbits(unsigned char *b, int minset, int maxset) {
  int sum = 0;
  for (int bit = minset; bit <= maxset; ++bit) {
    if (GETBIT(b, bit)) sum += bit;
  }
  return sum;
}

int main() {
  unsigned char buf[BUFSZ] = {};
  unsigned char buf2[BUFSZ] = {};
  int c, bit = 0;
  cin.ignore(20, ' ');
  cin.ignore(20, ' ');
  while ((c = cin.get()) != '\n') {
    SETBIT(buf, bit, CSET(c));
    ++bit;
  }
  cin.ignore(1);

  map<unsigned char, bool> rules;
  char l2, l1, c1, r1, r2, o;
  while (scanf("%c%c%c%c%c => %c\n",
               &l2, &l1, &c1, &r1, &r2, &o) == 6) {
    rules[CSET(l2) << 4 |
          CSET(l1) << 3 |
          CSET(c1) << 2 |
          CSET(r1) << 1 |
          CSET(r2) << 0] = CSET(o);
  }
  if (rules[0] != false) {
    cout << "..... => #? what? how?\n";
    return 1;
  }

  int minset = -1;
  int maxset = bit;
  unsigned char *b = buf, *tb = buf2;
  for (int i = 0; i < GENERATIONS; ++i) {
    advancef(b, tb, minset, maxset, rules);
    SWAP(b, tb);
  }

  cout << "Sum: " << sumbits(b, minset, maxset) << endl;

  for (int i = 0; i < GENERATIONS_WINDUP; ++i) {
    advancef(b, tb, minset, maxset, rules);
    SWAP(b, tb);
  }

  unsigned long long s = sumbits(b, minset, maxset);
  advancef(b, tb, minset, maxset, rules);
  unsigned long long ds = sumbits(tb, minset, maxset) - s;
  advancef(tb, b, minset, maxset, rules);
  if (sumbits(b, minset, maxset) - s != ds * 2) {
    cout << "What\n";
    return 1;
  }

  cout << "Big: " << (s + ds * (GENERATIONS_BIG - GENERATIONS_WINDUP - GENERATIONS)) << endl;
}
