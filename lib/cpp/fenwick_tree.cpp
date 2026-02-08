#include <vector>

using namespace std;

// Fenwick Tree (Binary Indexed Tree)
// 1-indexed 구현
struct FenwickTree {
  int n;
  vector<long long> tree;

  FenwickTree(int n) : n(n) { tree.resize(n + 1); }

  // idx에 val 더하기 (point update)
  void update(int idx, long long val) {
    while (idx <= n) {
      tree[idx] += val;
      idx += (idx & -idx);
    }
  }

  // 1 ~ idx 구간 합 (prefix sum)
  long long query(int idx) {
    long long sum = 0;
    while (idx > 0) {
      sum += tree[idx];
      idx -= (idx & -idx);
    }
    return sum;
  }

  // left ~ right 구간 합
  long long query(int left, int right) {
    return query(right) - query(left - 1);
  }
};
