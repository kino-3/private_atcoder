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

void debug_print() { cout << endl; }
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {
    std::cout << head << ", ";
    debug_print(std::forward<Tail>(tail)...);
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 10);
}
template <typename T>
void print_v(const vector<T> vec) {
    cout << "[";
    for (auto&& item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}
template <typename T>
void print_vv(const vector<T> vec) {
    for (auto&& item : vec) {
        print_v(item);
    }
}
template <typename K, typename V>
void print_map(const map<K, V> dict) {
    for (const auto v : dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v : data) {
        cout << v << ", ";
    }
    cout << endl;
}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {
    cout << "(" << data.first << "," << data.second << ")";
    // cout << endl;
}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {
    cout << "(";
    cout << get<0>(data) << "," << get<1>(data) << "," << get<2>(data);
    cout << ")";
    // cout << endl;
}

// 正の整数 n は素数か
// O(√n)
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

const ll mod = 998244353;
const ll RANGE = 200000;
ll N, M, Q, i, j, k, l;
vector<ll> A;
vector<ll> spf(RANGE + 1, 0);  // spf[i]: i の最小の素因数
vector<ll> primes;             // RANGE 以下の素数のリスト

// RANGE 以下の n の素因数分解
// spf を用いる
map<ll, ll> get_prime_factor(ll n) {
    map<ll, ll> prime_factor;
    while(n > 1) {
        ll prime = spf[n];
        if (prime_factor.count(prime) > 0) {
            prime_factor[prime] += 1;
        } else {
            prime_factor[prime] = 1;
        }
        n /= prime;
    }
    return prime_factor;
}

// RANGE^2 以下の n の素因数分解
// primes を用いる
map<ll, ll> get_prime_factor2(ll n) {
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

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }

    // 線形篩 O(N)
    FOR(i, 2, RANGE + 1) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (const auto p : primes) {
            if (p > spf[i] || p * i > RANGE) break;
            spf[p * i] = p;
        }
    }

    set<ll> found_primes;
    REP(i, N) {
        for (auto v: get_prime_factor(A[i])) {
            found_primes.insert(v.first);
        }
    }

    vector<bool> ans(M + 1, true);
    for (auto p : found_primes) {
        for (ll i = p; i <= M; i += p) {
            ans[i] = false;
        }
    }
    ll tmp = 0;
    FOR(i, 1, M + 1) {
        if (ans[i]) tmp++;
    }
    cout << tmp << endl;
    FOR(i, 1, M + 1) {
        if (ans[i]) cout << i << endl;
    }
}