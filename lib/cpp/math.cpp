#include <cmath>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>


using namespace std;

// 최대공약수 (GCD)
long long gcd(long long a, long long b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

// 최소공배수 (LCM)
long long lcm(long long a, long long b) {
  if (a == 0 || b == 0)
    return 0;
  return (a / gcd(a, b)) * b;
}

// 확장 유클리드 (ax + by = gcd(a, b) 해 찾기)
// 반환값: {g, x, y} -> g = ax + by
tuple<long long, long long, long long> extended_gcd(long long a, long long b) {
  if (b == 0)
    return {a, 1, 0};
  auto [g, x, y] = extended_gcd(b, a % b);
  return {g, y, x - (a / b) * y};
}

// 모듈러 역원 (a^-1 mod m)
// gcd(a, m) != 1 이면 존재하지 않음 (-1 반환)
long long modInverse(long long a, long long m) {
  auto [g, x, y] = extended_gcd(a, m);
  if (g != 1)
    return -1;
  return (x % m + m) % m;
}

// 빠른 거듭제곱 (base^exp % mod)
long long power(long long base, long long exp, long long mod) {
  long long res = 1;
  base %= mod;
  while (exp > 0) {
    if (exp % 2 == 1)
      res = (res * base) % mod;
    base = (base * base) % mod;
    exp /= 2;
  }
  return res;
}

// 에라토스테네스의 체 (소수 판별)
vector<bool> sieve(int n) {
  vector<bool> is_prime(n + 1, true);
  is_prime[0] = is_prime[1] = false;
  for (int p = 2; p * p <= n; p++) {
    if (is_prime[p]) {
      for (int i = p * p; i <= n; i += p)
        is_prime[i] = false;
    }
  }
  return is_prime;
}

// 오일러 피 함수 (1~n 중 n과 서로소인 수의 개수)
long long euler_phi(long long n) {
  long long result = n;
  for (long long i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0)
        n /= i;
      result -= result / i;
    }
  }
  if (n > 1)
    result -= result / n;
  return result;
}

// 조합 (nCr % mod) - 팩토리얼 미리 계산 필요
const int MAX = 1000005;
const int MOD = 1e9 + 7;
long long fact[MAX], invFact[MAX];

void precomputeFactorial() {
  fact[0] = 1;
  for (int i = 1; i < MAX; i++)
    fact[i] = (fact[i - 1] * i) % MOD;
  invFact[MAX - 1] = power(fact[MAX - 1], MOD - 2, MOD);
  for (int i = MAX - 2; i >= 0; i--)
    invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
}

long long nCr(int n, int r) {
  if (r < 0 || r > n)
    return 0;
  return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}
