#include <iostream>
#include <string>
#include <vector>


using namespace std;

// KMP Failure Function
vector<int> getPi(string p) {
  int m = p.size(), j = 0;
  vector<int> pi(m, 0);
  for (int i = 1; i < m; i++) {
    while (j > 0 && p[i] != p[j])
      j = pi[j - 1];
    if (p[i] == p[j])
      pi[i] = ++j;
  }
  return pi;
}

// KMP Search
vector<int> kmp(string s, string p) {
  vector<int> ans;
  auto pi = getPi(p);
  int n = s.size(), m = p.size(), j = 0;
  for (int i = 0; i < n; i++) {
    while (j > 0 && s[i] != p[j])
      j = pi[j - 1];
    if (s[i] == p[j]) {
      if (j == m - 1) {
        ans.push_back(i - m + 1);
        j = pi[j];
      } else
        j++;
    }
  }
  return ans;
}

// Trie Node
struct TrieNode {
  TrieNode *children[26];
  bool isEnd;

  TrieNode() {
    for (int i = 0; i < 26; i++)
      children[i] = nullptr;
    isEnd = false;
  }

  ~TrieNode() {
    for (int i = 0; i < 26; i++)
      if (children[i])
        delete children[i];
  }
};

// Trie Insert/Search
void insert(TrieNode *root, string key) {
  TrieNode *curr = root;
  for (char c : key) {
    int idx = c - 'a';
    if (!curr->children[idx])
      curr->children[idx] = new TrieNode();
    curr = curr->children[idx];
  }
  curr->isEnd = true;
}

bool search(TrieNode *root, string key) {
  TrieNode *curr = root;
  for (char c : key) {
    int idx = c - 'a';
    if (!curr->children[idx])
      return false;
    curr = curr->children[idx];
  }
  return curr != nullptr && curr->isEnd;
}
