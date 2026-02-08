# Suffix Array & LCP

## 📌 Suffix Array (접미사 배열)
문자열의 모든 접미사를 **사전순 정렬**한 배열.

---

## 💻 O(N log²N) 구현
```cpp
string s;
int n, sa[MAX], rank_[MAX], tmp[MAX];

bool cmp(int a, int b, int d) {
    if (rank_[a] != rank_[b]) return rank_[a] < rank_[b];
    int ra = a + d < n ? rank_[a + d] : -1;
    int rb = b + d < n ? rank_[b + d] : -1;
    return ra < rb;
}

void buildSA() {
    n = s.size();
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank_[i] = s[i];
    }
    
    for (int d = 1; d < n; d *= 2) {
        sort(sa, sa + n, [d](int a, int b) { return cmp(a, b, d); });
        
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i-1]] + cmp(sa[i-1], sa[i], d);
        }
        copy(tmp, tmp + n, rank_);
    }
}
```

---

## 💻 LCP (Longest Common Prefix)
인접한 접미사들의 공통 접두사 길이.

```cpp
int lcp[MAX];

void buildLCP() {
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank_[i] == 0) continue;
        
        int j = sa[rank_[i] - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        
        lcp[rank_[i]] = k;
        if (k > 0) k--;
    }
}
```

---

## 🎯 활용
- **서로 다른 부분 문자열 개수**: N(N+1)/2 - Σlcp[i]
- **패턴 검색**: 이분 탐색으로 O(M log N)
- **가장 긴 반복 부분 문자열**: max(lcp[i])

---

### 💡 접미사 배열 & LCP
- **Suffix Array**: 모든 접미사를 사전순 정렬했을 때의 시작 인덱스 배열
- **LCP Array**: 정렬된 접미사들 중 '인접한 두 접미사'의 최장 공통 접두사 길이
- 예: `banana`
  - 접미사: banana, anana, nana, ana, na, a
  - 정렬: a, ana, anana, banana, na, nana
  - SA: [5, 3, 1, 0, 4, 2]
  - LCP: [x, 1, 3, 0, 0, 2]

### 🎓 실전 팁
1. **부분 문자열 개수**: `N*(N+1)/2 - sum(LCP)`
2. **최장 반복 부분 문자열**: `max(LCP)`
3. **구현**: O(Nlog²N) 방식이 구현 간단 (맨버-마이어스), O(N)은 복잡함
4. **문자열 압축/패턴 찾기**: Suffix Array + LCP 조합으로 강력한 해결 가능

## 📚 연습 문제
- [BOJ 9248 Suffix Array](https://www.acmicpc.net/problem/9248) ⭐⭐⭐⭐
- [BOJ 11479 서로 다른 부분 문자열의 개수 2](https://www.acmicpc.net/problem/11479) ⭐⭐⭐⭐
- [BOJ 3033 가장 긴 문자열](https://www.acmicpc.net/problem/3033) ⭐⭐⭐⭐⭐
