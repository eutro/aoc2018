#include <iostream>
#include <map>
#include <set>
using namespace std;

#define WORKERS 5
#define DURATION(step) (61 + (step) - 'A')

class Rule {
public:
  set<char> dependencies;
  set<char> dependents;
};

int main() {
  char dependency, dependent;
  set<char> start_rules;
  map<char, Rule> rules;
  while (scanf("Step %c must be finished before step %c can begin.\n", &dependency, &dependent) == 2) {
    auto dep = &rules[dependency];
    if (dep->dependencies.empty()) start_rules.insert(dependency);
    dep->dependents.insert(dependent);
    rules[dependent].dependencies.insert(dependency);
    start_rules.erase(dependent);
  }

  cout << "Steps: ";
  set<char> available = start_rules;
  map<char, Rule> rulesc = rules;
  while (!available.empty()) {
    char r = *available.begin();
    available.erase(r);
    cout << r;
    for (char e : rulesc[r].dependents) {
      auto d = &rulesc[e].dependencies;
      d->erase(r);
      if (d->empty()) available.insert(e);
    }
  }
  cout << endl;

  available = start_rules;
  rulesc = rules;
  map<int, char> jobs;
  int time = 0;
  do {
    while (jobs.size() < WORKERS && !available.empty()) {
      char r = *available.begin();
      available.erase(r);
      jobs[time + DURATION(r)] = r;
    }
    auto job = jobs.begin();
    char r = job->second;
    jobs.erase(time = job->first);
    for (char e : rulesc[r].dependents) {
      auto d = &rulesc[e].dependencies;
      d->erase(r);
      if (d->empty()) available.insert(e);
    }
  } while (!jobs.empty() || !available.empty());
  cout << "Time: " << time << endl;
}
