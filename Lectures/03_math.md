# 수학 & 정수론 (Math & Number Theory)

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "최대공약수/최소공배수" → GCD/LCM
- "소수 판별" → 에라토스테네스 체
- "1부터 N까지의 소수 개수" → 에라토스테네스
- "X^N mod M" → 빠른 거듭제곱
- "nCr mod M" → 조합 + 모듈러 역원
- "N!에서 0의 개수" → 5의 개수 세기

## 📌 핵심 개념

### 1. 최대공약수 (GCD) & 최소공배수 (LCM)
```cpp
// 유클리드 호제법 O(log(min(a,b)))
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int lcm(int a, int b) {
    return a / gcd(a, b) * b;  // 오버플로우 방지
}

// C++17 이상: __gcd(a, b) 또는 gcd(a, b)
```

```python
import math
math.gcd(a, b)
math.lcm(a, b)  # Python 3.9+
```

### 2. 소수 판별 & 에라토스테네스의 체
```cpp
// 단일 소수 판별 O(√N)
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

// 에라토스테네스의 체 O(NloglogN)
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++)
        if (is_prime[i])
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
    return is_prime;
}
```

```python
def sieve(n):
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(n**0.5) + 1):
        if is_prime[i]:
            for j in range(i*i, n+1, i):
                is_prime[j] = False
    return is_prime
```

### 3. 거듭제곱 & 모듈러 연산
```cpp
// 빠른 거듭제곱 O(logN)
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

// 모듈러 역원 (mod가 소수일 때)
// a^(-1) ≡ a^(p-2) (mod p) - 페르마의 소정리
long long modInverse(long long a, long long mod) {
    return power(a, mod - 2, mod);
}
```

### 4. 조합 (nCr)
```cpp
// 파스칼 삼각형으로 전처리 O(N²)
long long C[1001][1001];
void precompute() {
    for (int i = 0; i <= 1000; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
    }
}

// 팩토리얼 + 역원으로 계산 O(N + logMOD)
long long fact[MAX], inv_fact[MAX];
void init() {
    fact[0] = 1;
    for (int i = 1; i < MAX; i++) fact[i] = fact[i-1] * i % MOD;
    inv_fact[MAX-1] = power(fact[MAX-1], MOD-2, MOD);
    for (int i = MAX-2; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
}
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] % MOD * inv_fact[n-r] % MOD;
}
```

## 📖 외부 자료
- [Number Theory - CP Algorithms](https://cp-algorithms.com/)
- [에라토스테네스의 체 시각화](https://www.youtube.com/watch?v=V08g_lkKj6Q)

## 📚 연습 문제
- [BOJ 2609 최대공약수와 최소공배수](https://www.acmicpc.net/problem/2609)
- [BOJ 1929 소수 구하기](https://www.acmicpc.net/problem/1929) ⭐ 에라토스테네스
- [BOJ 1676 팩토리얼 0의 개수](https://www.acmicpc.net/problem/1676)
- [BOJ 11050 이항 계수 1](https://www.acmicpc.net/problem/11050)
