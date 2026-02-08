#include <algorithm>
#include <cmath>
#include <vector>


using namespace std;

struct Query {
  int l, r, idx;
};

int sqrtN;

bool compare(const Query &a, const Query &b) {
  if (a.l / sqrtN != b.l / sqrtN)
    return a.l / sqrtN < b.l / sqrtN;
  return (a.l / sqrtN) % 2 == 1
             ? a.r < b.r
             : a.r > b.r; // Hilbert Curve optimization variant
}

// 전역 변수들 (문제에 따라 수정)
int cnt[1000005];
int res = 0;
vector<int> arr;

void add(int idx) {
  if (++cnt[arr[idx]] == 1)
    res++; // 예: 서로 다른 수 개수
}

void remove(int idx) {
  if (--cnt[arr[idx]] == 0)
    res--;
}

vector<int> mos_algorithm(int n, const vector<int> &input_arr,
                          vector<Query> &queries) {
  arr = input_arr;
  sqrtN = sqrt(n);
  sort(queries.begin(), queries.end(), compare);

  vector<int> ans(queries.size());
  int l = queries[0].l, r = queries[0].l - 1;

  for (const auto &q : queries) {
    while (l > q.l)
      add(--l);
    while (r < q.r)
      add(++r);
    while (l < q.l)
      remove(l++);
    while (r > q.r)
      remove(r--);
    ans[q.idx] = res;
  }
  return ans;
}
