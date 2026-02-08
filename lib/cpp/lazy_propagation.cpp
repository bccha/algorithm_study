#include <vector>

using namespace std;

// 구간 합 + 구간 더하기 Lazy Propagation
struct LazySegmentTree {
  int n;
  vector<long long> tree;
  vector<long long> lazy;

  LazySegmentTree(int n) : n(n) {
    tree.resize(4 * n);
    lazy.resize(4 * n);
  }

  // Lazy 전파
  void propagate(int node, int start, int end) {
    if (lazy[node] != 0) {
      tree[node] += (end - start + 1) * lazy[node];
      if (start != end) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
      }
      lazy[node] = 0;
    }
  }

  void update(int node, int start, int end, int left, int right,
              long long val) {
    propagate(node, start, end);

    if (left > end || right < start)
      return;

    if (left <= start && end <= right) {
      lazy[node] += val;
      propagate(node, start, end);
      return;
    }

    int mid = (start + end) / 2;
    update(node * 2, start, mid, left, right, val);
    update(node * 2 + 1, mid + 1, end, left, right, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

  long long query(int node, int start, int end, int left, int right) {
    propagate(node, start, end);

    if (left > end || right < start)
      return 0;
    if (left <= start && end <= right)
      return tree[node];

    int mid = (start + end) / 2;
    return query(node * 2, start, mid, left, right) +
           query(node * 2 + 1, mid + 1, end, left, right);
  }
};
