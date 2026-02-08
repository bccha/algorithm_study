#include <algorithm>
#include <cmath>
#include <vector>


using namespace std;

// 구간 합 세그먼트 트리
struct SegmentTree {
  int n;
  vector<long long> tree;

  SegmentTree(int n) : n(n) { tree.resize(4 * n); }

  // 초기화
  void init(const vector<long long> &arr, int node, int start, int end) {
    if (start == end) {
      tree[node] = arr[start];
      return;
    }
    int mid = (start + end) / 2;
    init(arr, node * 2, start, mid);
    init(arr, node * 2 + 1, mid + 1, end);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

  // 쿼리 (left ~ right 구간 합)
  long long query(int node, int start, int end, int left, int right) {
    if (left > end || right < start)
      return 0;
    if (left <= start && end <= right)
      return tree[node];

    int mid = (start + end) / 2;
    return query(node * 2, start, mid, left, right) +
           query(node * 2 + 1, mid + 1, end, left, right);
  }

  // 업데이트 (update idx with val)
  // diff를 더하는 방식
  void update(int node, int start, int end, int idx, long long diff) {
    if (idx < start || idx > end)
      return;

    tree[node] += diff;
    if (start != end) {
      int mid = (start + end) / 2;
      update(node * 2, start, mid, idx, diff);
      update(node * 2 + 1, mid + 1, end, idx, diff);
    }
  }
};

// 사용법
// SegmentTree st(n);
// st.init(arr, 1, 1, n); (1-indexed)
// st.query(1, 1, n, left, right);
// st.update(1, 1, n, idx, diff);
