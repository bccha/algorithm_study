import math

# 최대공약수 (GCD)
def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

# 최소공배수 (LCM)
def lcm(a, b):
    if a == 0 or b == 0: return 0
    return abs(a * b) // gcd(a, b)

# 확장 유클리드 (ax + by = gcd(a, b))
# 반환: (g, x, y)
def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    g, x, y = extended_gcd(b, a % b)
    return g, y, x - (a // b) * y

# 모듈러 역원 (a^-1 mod m)
def mod_inverse(a, m):
    g, x, y = extended_gcd(a, m)
    if g != 1:
        return None  # 역원 존재 X
    return (x % m + m) % m

# 빠른 거듭제곱 (base^exp % mod)
# Python 내장 pow(base, exp, mod) 사용 권장
def power(base, exp, mod):
    return pow(base, exp, mod)

# 에라토스테네스의 체
def sieve(n):
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    for p in range(2, int(n**0.5) + 1):
        if is_prime[p]:
            for i in range(p * p, n + 1, p):
                is_prime[i] = False
    return is_prime

# 오일러 피 함수
def euler_phi(n):
    result = n
    p = 2
    while p * p <= n:
        if n % p == 0:
            while n % p == 0:
                n //= p
            result -= result // p
        p += 1
    if n > 1:
        result -= result // n
    return result

# 조합 (nCr % mod)
class Combinatorics:
    def __init__(self, n, mod):
        self.mod = mod
        self.fact = [1] * (n + 1)
        self.inv = [1] * (n + 1)
        
        for i in range(1, n + 1):
            self.fact[i] = (self.fact[i - 1] * i) % mod
            
        self.inv[n] = pow(self.fact[n], mod - 2, mod)
        for i in range(n - 1, -1, -1):
            self.inv[i] = (self.inv[i + 1] * (i + 1)) % mod
            
    def nCr(self, n, r):
        if r < 0 or r > n: return 0
        num = self.fact[n]
        den = (self.inv[r] * self.inv[n - r]) % self.mod
        return (num * den) % self.mod
