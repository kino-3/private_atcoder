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
void debug_print(Head &&head, Tail &&...tail) {
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
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}
template <typename T>
void print_vv(const vector<T> vec) {
    for (auto &&item : vec) {
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
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {
    for (auto &&item : vec) {
        print_pair(item);
    }
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

const ll mod = 998244353;
ll L, R, i, j, k, l;
string S, T;
vector<ll> primes;

vector<ll> dfs(ll count, ll prime = 2, ll tmp = 1) {
    // prime 以上の素数の count 個の積
    vector<ll> res;
    if (count == 0) {
        res.push_back(1);
        return res;
    }
    for (auto p : primes) {
        if (p < prime) continue;
        if (p * tmp > R * 3) break;
        for (auto vv : dfs(count - 1, p + 1, tmp * p)) {
            if (vv * tmp <= R * 3) {
                res.push_back(vv * p);
            } else {
                break;
            }
        }
    }
    return res;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> L >> R;
    primes = list_primes(R / 3 + 1);
    ll pair_ans = 0;
    ll count = 1;
    while (true) {
        // 素数が count 個
        auto prod = dfs(count);
        // print_v(prod);
        debug_print(prod.size());
        if (prod.size() == 0) break;
        ll ans = 0;
        if (count % 2 == 1) {
            pair_ans += ans;
        } else {
            pair_ans -= ans;
        }
        count ++;
    }
    cout << pair_ans * 2 << endl;
}