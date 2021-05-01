#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
  vector<Node> children;
  vector<int> metadata;
};

long long meta_sum = 0;

Node read_node() {
  Node n;
  int children, metadata;
  cin >> children >> metadata;
  for (int i = 0; i < children; ++i) {
    n.children.push_back(read_node());
  }
  for (int i = 0; i < metadata; ++i) {
    int entry;
    cin >> entry;
    n.metadata.push_back(entry);
    meta_sum += entry;
  }
  return n;
}

long long node_value(Node &n) {
  long long v = 0;
  if (n.children.empty()) {
    for (int i : n.metadata) v += i;
  } else {
    for (int i : n.metadata) {
      if (i == 0 || i > n.children.size()) continue;
      v += node_value(n.children[i - 1]);
    }
  }
  return v;
}

int main() {
  Node root = read_node();
  cout << "Meta: " << meta_sum << endl;
  cout << "Value: " << node_value(root) << endl;
}
