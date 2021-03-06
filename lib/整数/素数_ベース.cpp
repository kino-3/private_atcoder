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

// 正の整数 n は素数か
bool is_prime(ll n) {
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    if (n == 1) {
        return false;
    }
    return true;
}

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

// {3: 1, 5: 2} なら
// [1*1, 3*1, 1*5, 3*5, 1*25, 3*25] を返す
vector<ll> create_product(map<ll, ll> m) {
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

// n の約数を列挙する
// 動作確認: https://atcoder.jp/contests/typical90/tasks/typical90_cg
vector<ll> list_factor(ll n) {
    vector<ll> list_factor = create_product(get_prime_factor(n));
    sort(list_factor.begin(), list_factor.end());
    return list_factor;
}

const ll mod = 998244353;
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    B.resize(N);
    REP(i, N) {
        cin >> A[i] >> B[i];
    }
}