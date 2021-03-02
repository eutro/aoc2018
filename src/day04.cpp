#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string.h>
using namespace std;

#define MINUTES 60

class Entry {
public:
  int month, day, hour, minute, guard;
  bool awake;

  bool operator<(const Entry &other) {
    return
      (this->month < other.month ||
       (this->month == other.month &&
        (this->day < other.day ||
         (this->day == other.day &&
          (this->hour < other.hour ||
           (this->hour == other.hour &&
            this->minute < other.minute))))));
  }
};

class Day {
public:
  int month, day, guard;
  bool awake[MINUTES];
};

void print_entry(Entry entry) {
  printf("[1518-%02d-%02d %02d:%02d] ",
         entry.month,
         entry.day,
         entry.hour,
         entry.minute);
  if (entry.guard != -1) {
    cout << "Guard #" << entry.guard << " begins shift";
  } else {
    cout << (entry.awake ? "wakes up" : "falls asleep");
  }
  cout << endl;
}

void print_day(Day day) {
  printf("%02d-%02d #%04d ", day.month, day.day, day.guard);
  for (int i = 0; i < MINUTES; ++i) {
    cout << (day.awake[i] ? '.' : '#');
  }
  cout << endl;
}

int main() {
  vector<Entry> entries;
  Entry entry;
  while (scanf("[1518-%d-%d %d:%d] ",
               &entry.month,
               &entry.day,
               &entry.hour,
               &entry.minute) == 4) {
    string line;
    getline(cin, line);
    if (sscanf(line.c_str(), "Guard #%d begins shift", &entry.guard) != 1) {
      entry.guard = -1;
      entry.awake = "wakes up" == line;
    } else {
      entry.awake = true;
    }
    entries.push_back(entry);
  }
  sort(entries.begin(), entries.end());
  vector<Day> days;
  Day day;
  day.guard = -1;
  bool awake = true;
  int start = 0;
  for (Entry entry : entries) {
    if (entry.guard != -1) {
      if (day.guard != -1) {
        memset(&day.awake[start], awake, MINUTES - start);
        days.push_back(day);
      }
      day.guard = entry.guard;
      awake = true;
      start = 0;
    } else {
      memset(&day.awake[start], awake, entry.minute - start);
      start = entry.minute;
      awake = entry.awake;
      day.month = entry.month;
      day.day = entry.day;
    }
  }
  memset(&day.awake[start], awake, MINUTES - start);
  days.push_back(day);

  /*
  cout << "Date  ID    Minute" << endl;
  cout << "            000000000011111111112222222222333333333344444444445555555555" << endl;
  cout << "            012345678901234567890123456789012345678901234567890123456789" << endl;
  for (Day day : days) print_day(day);
  */

  map<int, int> sleptc;
  map<int, int[MINUTES]> sleptms;
  for (Day day : days) {
    for (int m = 0; m < MINUTES; ++m) {
      if (!day.awake[m]) {
        sleptc[day.guard]++;
        sleptms[day.guard][m]++;
      }
    }
  }
  int maxs = 0;
  int max_guard = -1;
  for (auto guard : sleptc) {
    if (guard.second > maxs) {
      max_guard = guard.first;
      maxs = guard.second;
    }
  }
  maxs = 0;
  int maxm = -1;
  for (int m = 0; m < MINUTES; ++m) {
    if (sleptms[max_guard][m] > maxs) {
      maxm = m;
      maxs = sleptms[max_guard][m];
    }
  }
  cout << max_guard << " * " << maxm << " = " << max_guard * maxm << endl;

  maxs = 0;
  max_guard = -1;
  maxm = -1;
  for (auto entry : sleptms) {
    for (int m = 0; m < MINUTES; ++m) {
      if (entry.second[m] > maxs) {
        max_guard = entry.first;
        maxm = m;
        maxs = entry.second[m];
      }
    }
  }
  cout << max_guard << " * " << maxm << " = " << max_guard * maxm << endl;
}
