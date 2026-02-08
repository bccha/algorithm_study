# 문자열 알고리즘 (KMP, Trie, Aho-Corasick)

## 1️⃣ KMP (Knuth-Morris-Pratt)
패턴### 💡 KMP 알고리즘 (실패 함수)
문자열 `S`에서 패턴 `P`를 찾을 때, 불일치 발생 시 얼마나 점프할지 미리 계산.
- `pi[i]`: `P[0...i]`의 접두사와 접미사가 일치하는 최대 길이
- 불일치 시 `j = pi[j-1]`로 이동하여 앞부분 재사용!

### 🎓 실전 팁
1. **KMP vs 라빈카프**: KMP는 해시 충돌 걱정 없음 (안정적)
2. **Trie**: 문자열 집합 검색에 강력 (메모리 주의: `Node* next[26]`)
3. **아호-코라식**: "여러 패턴"을 동시에 찾을 때 (Trie + KMP 실패함수)
4. **문자열 매칭**: 단순 `find`는 O(NM)이라 시간초과, KMP는 O(N+M)
### 실패 함수 (Failure Function)
```cpp
vector<int> getFailure(string& pattern) {
    int m = pattern.size();
    vector<int> fail(m, 0);
    
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j])
            j = fail[j-1];
        if (pattern[i] == pattern[j])
            fail[i] = ++j;
    }
    return fail;
}
```

### 패턴 검색
```cpp
vector<int> kmp(string& text, string& pattern) {
    vector<int> fail = getFailure(pattern);
    vector<int> matches;
    
    int j = 0;
    for (int i = 0; i < text.size(); i++) {
        while (j > 0 && text[i] != pattern[j])
            j = fail[j-1];
        if (text[i] == pattern[j]) {
            j++;
            if (j == pattern.size()) {
                matches.push_back(i - j + 1);
                j = fail[j-1];
            }
        }
    }
    return matches;
}
```

---

## 2️⃣ Trie (트라이)
문자열 집합의 접두사 검색: O(문자열 길이)

```cpp
struct Trie {
    Trie* children[26];
    bool isEnd;
    
    Trie() {
        fill(children, children + 26, nullptr);
        isEnd = false;
    }
    
    void insert(string& s) {
        Trie* cur = this;
        for (char c : s) {
            int idx = c - 'a';
            if (!cur->children[idx])
                cur->children[idx] = new Trie();
            cur = cur->children[idx];
        }
        cur->isEnd = true;
    }
    
    bool search(string& s) {
        Trie* cur = this;
        for (char c : s) {
            int idx = c - 'a';
            if (!cur->children[idx]) return false;
            cur = cur->children[idx];
        }
        return cur->isEnd;
    }
};
```

---

## 3️⃣ Aho-Corasick
여러 패턴 동시 검색: O(N + M + 매칭 수)

```cpp
// Trie + 실패 링크 (BFS로 구축)
struct AhoCorasick {
    Trie* root;
    
    void buildFailure() {
        queue<Trie*> q;
        root->fail = root;
        
        for (int i = 0; i < 26; i++) {
            if (root->children[i]) {
                root->children[i]->fail = root;
                q.push(root->children[i]);
            }
        }
        
        while (!q.empty()) {
            Trie* cur = q.front(); q.pop();
            
            for (int i = 0; i < 26; i++) {
                if (cur->children[i]) {
                    Trie* fail = cur->fail;
                    while (fail != root && !fail->children[i])
                        fail = fail->fail;
                    cur->children[i]->fail = fail->children[i] ? fail->children[i] : root;
                    q.push(cur->children[i]);
                }
            }
        }
    }
};
```

---

## 📚 연습 문제
- [BOJ 1786 찾기](https://www.acmicpc.net/problem/1786) ⭐⭐⭐ KMP
- [BOJ 5052 전화번호 목록](https://www.acmicpc.net/problem/5052) ⭐⭐⭐ Trie
- [BOJ 14725 개미굴](https://www.acmicpc.net/problem/14725) ⭐⭐⭐ Trie
- [BOJ 9250 문자열 집합 판별](https://www.acmicpc.net/problem/9250) ⭐⭐⭐⭐ Aho-Corasick
