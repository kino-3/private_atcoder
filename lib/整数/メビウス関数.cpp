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

// n 以下の素数を列挙する
// 素数で割れるか考えるよりも, エラトステネスの篩の方が速かった
// https://atcoder.jp/contests/typical90/tasks/typical90_ad
vector<ll> list_primes(ll n) {
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

// n を素因数分解する
map<ll, ll> get_prime_factor(ll n) {
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

// メビウス関数のマップ
// res[d] == μ(d)
// ただし, d は n の約数のうち, μ(d) != 0 のもののみ
map<ll, ll> moebius(ll n) {
    map<ll, ll> res;
    vector<ll> primes;
    for (auto v : get_prime_factor(n)) {
        primes.push_back(v.first);
    }
    ll sz = primes.size();
    for (ll i = 0; i < (1 << sz); i++) {
        ll mu = 1;
        ll d = 1;
        std::bitset<100> bs(i);
        for (ll j = 0; j < sz; j++) {
            if (bs[j]) {
                d *= primes[j];
                mu *= -1;
            }
        }
        res[d] = mu;
    }
    return res;
}

const ll mod = 998244353;
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

ll f(ll n) { return n; }

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;

    // f(n) = Σ g(d)  (Σはnの全ての約数dに置ける和)
    // ⇔
    // g(d) = Σ μ(n/d)*f(d)
    //    ( = Σ μ(d)*f(n/d) )
    //
    // - g(n) を求めたい
    // - Σ g(d) (dはnの約数) は簡単に分かる
    // ときに使う (多分)

    ll ans = 0;
    map<ll, ll> mu = moebius(N);
    for (auto d : mu) {
        ans += d.second * f(N / d.first);
    }
}