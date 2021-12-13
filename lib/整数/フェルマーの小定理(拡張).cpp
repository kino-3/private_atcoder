#include <bits/stdc++.h>
#define REP(var, n) for (decltype(n) var = 0; var < (n); var++)
#define REP_R(var, n) \
    for (auto var = (n)-1; var != static_cast<decltype(var)>(-1); var--)
#define FOR(var, a, b) for (auto var = (a); var < (b); var++)
#define FOR_R(var, a, b) for (auto var = (b - 1); var > (a - 1); var--)
#define ALL(c) std::begin(c), std::end(c)

using namespace std;
using ll = long long;

// REP(idx, 3) { cout << idx; }  // 012
// REP_R(idx, 3) { cout << idx; }  // 210
// FOR(idx, 4, 7) { cout << idx; }  // 456
// FOR_R(idx, 4, 7) { cout << idx; }  // 654
// sort(ALL(v));


const ll mod = 998244353;
ll N, i;
string S;

vector<ll> list_primes(ll n) {
    // n 以下の素数を列挙する
    // 素数で割れるか考えるよりも, エラトステネスの篩の方が速かった
    // https://atcoder.jp/contests/typical90/tasks/typical90_ad
    if (n == 1) {
        return vector<ll>(0);
    }
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            for (ll idx = i * i; idx <= n; idx += i) {
                is_prime[idx] = false;
            }
        }
    }
    vector<ll> primes;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

map<ll, ll> get_prime_factor(ll n) {
    // n を素因数分解する
    vector<ll> primes = list_primes(static_cast<ll>(sqrt(n)) + 1);
    map<ll, ll> prime_factor;
    for (const auto& prime : primes) {
        while (true) {
            if (n % prime == 0) {
                if (prime_factor.count(prime) > 0) {
                    prime_factor[prime] += 1;
                } else {
                    prime_factor[prime] = 1;
                }
                n /= prime;
            } else {
                break;
            }
        }
    }
    if (n != 1) {
        prime_factor[n] = 1;  // √n より大きな素因数
    }
    return prime_factor;
}

vector<ll> create_product(map<ll, ll> m) {
    // {3: 1, 5: 2} なら
    // [1*1, 3*1, 1*5, 3*5, 1*25, 3*25] を返す
    vector<ll> result;
    if (m.size() == 0) {
        result.push_back(1);
        return result;
    }
    auto itr = m.begin();
    ll prime = itr->first;
    ll count = itr->second;
    m.erase(itr);
    ll p = 1;
    for (int i = 0; i <= count; i++) {
        for (const auto& q : create_product(m)) {
            result.push_back(p * q);
        }
        p *= prime;
    }
    return result;
}

// x^n % mod を返す
ll mod_pow(ll x, ll n, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) {
            res = res * x % mod;
        }
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

// 1 以上 modulo 以下の自然数のうち, modulo と互いに素である任意の自然数 b について
// b^n ≡ 1 (mod modulo) となる最小の n
ll carmichael(ll modulo) {
    auto primes = get_prime_factor(modulo);
    if (primes.size() == 1) {
        ll pp = (primes.begin())->first;
        ll nn = (primes.begin())->second;
        if (pp == 2) {
            if (nn == 1) {
                return 1;
            } else if (nn == 2) {
                return 2;
            } else if (nn > 2) {
                ll pow = 1;
                REP(j, nn - 2) pow *= 2;
                return pow;
            }
        } else {
            ll pow = pp - 1;
            REP(j, nn - 1) pow *= pp;
            return pow;
        }
    }
    ll lcm = 1;
    for (auto it = primes.begin(); it != primes.end(); ++it) {
        ll pp = it->first;
        ll nn = it->second;
        ll pow = 1;
        REP(i, nn) pow *= pp;
        ll cc = carmichael(pow);
        lcm = lcm * cc / __gcd(cc, lcm);
    }
    return lcm;
}

// modulo と互いに素である任意の自然数 b について
// b^n ≡ 1 (mod modulo) となる n (最小とは限らない)
// いわゆるオイラー関数である
ll euler(ll modulo) {
    auto primes = get_prime_factor(modulo);
    ll res = 1;
    for (auto it = primes.begin(); it != primes.end(); ++it) {
        ll pp = it->first;
        ll nn = it->second;
        res *= pp - 1;
        REP(i, nn - 1) res *= pp;
    }
    return res;
}

// base^n ≡ 1 (mod modulo) となる n の最小値
// 動作確認: https://atcoder.jp/contests/abc222/tasks/abc222_g
ll euler_withbase(ll base, ll modulo) {
    if (__gcd(base, modulo) > 1) return -1;
    ll tmp = euler(modulo);
    auto divisors = create_product(get_prime_factor(tmp));
    sort(divisors.begin(), divisors.end());
    for (const auto div : divisors) {
        if (mod_pow(base, div, modulo) == 1) return div;
    }
    assert (false);
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    cout << N << endl;
}