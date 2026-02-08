#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

// Suffix Array (O(Nlog^2N))
vector<int> getSuffixArray(const string &s) {
  int n = s.size();
  vector<int> sa(n), rank(n);
  vector<int> new_rank(n);

  for (int i = 0; i < n; i++) {
    sa[i] = i;
    rank[i] = s[i];
  }

  for (int d = 1; d < n; d *= 2) {
    auto cmp = [&](int i, int j) {
      if (rank[i] != rank[j])
        return rank[i] < rank[j];
      int ri = (i + d < n) ? rank[i + d] : -1;
      int rj = (j + d < n) ? rank[j + d] : -1;
      return ri < rj;
    };

    sort(sa.begin(), sa.end(), cmp);

    new_rank[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
      if (cmp(sa[i - 1], sa[i]))
        new_rank[sa[i]] = new_rank[sa[i - 1]] + 1;
      else
        new_rank[sa[i]] = new_rank[sa[i - 1]];
    }
    rank = new_rank;
    if (rank[sa[n - 1]] == n - 1)
      break;
  }
  return sa;
}

// LCP Array (O(N)) - using Kasai's algorithm
vector<int> getLCP(const string &s, const vector<int> &sa) {
  int n = s.size();
  vector<int> rank(n), lcp(n);
  for (int i = 0; i < n; i++)
    rank[sa[i]] = i;

  int h = 0;
  for (int i = 0; i < n; i++) {
    if (rank[i] > 0) {
      int j = sa[rank[i] - 1];
      while (i + h < n && j + h < n && s[i + h] == s[j + h])
        h++;
      lcp[rank[i]] = h;
      if (h > 0)
        h--;
    }
  }
  return lcp;
}
