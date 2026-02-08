#include <numeric>
#include <vector>


using namespace std;

// Disjoint Set Union (Union-Find)
struct DSU {
  vector<int> parent;
  vector<int> size; // 그룹 크기 추적

  DSU(int n) {
    parent.resize(n + 1);
    iota(parent.begin(), parent.end(), 0); // 0, 1, 2, ...
    size.assign(n + 1, 1);
  }

  int find(int x) {
    if (parent[x] == x)
      return x;
    return parent[x] = find(parent[x]); // 경로 압축
  }

  bool unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
      return false;

    // Union by Size (더 큰 쪽으로 합치기)
    if (size[a] < size[b])
      swap(a, b);
    parent[b] = a;
    size[a] += size[b];
    return true;
  }

  bool same(int a, int b) { return find(a) == find(b); }

  int getSize(int x) { return size[find(x)]; }
};
