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

template <typename T>
void debug_print(const T item) {
    cout << item << endl;
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
    for (auto it = dict.begin(); it != dict.end(); ++it) {
        cout << it->first << ":" << it->second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (auto it = data.begin(); it != data.end(); ++it) {
        cout << *it << ", ";
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

const ll mod = 998244353;
ll N, i, j, k, l;
vector<ll> A, B;

template <typename T>
vector<T> deep_copy_1d(const vector<T> vec) {
    vector<T> tmp(vec.size());
    for (const auto &item : vec) {
        tmp.push_back(item);
    }
    return vec;
}

template <typename T>
vector<vector<T>> deep_copy_2d(const vector<vector<T>> vec) {
    vector<vector<T>> tmp(vec.size());
    for (const auto &item : vec) {
        tmp.push_back(deep_copy_1d(item));
    }
    return vec;
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

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    set<ll> data;
    REP(i, N) {
        cin >> A[i];
        data.insert(A[i]);
    }

    vector<ll> B = deep_copy_1d(A);
    sort(ALL(B));

    vector<ll> leq;
    REP(i, N) {
        leq.push_back(
            N - distance(B.begin(), lower_bound(B.begin(), B.end(), A[i])) - 1);
    }

    multiset<ll> cnt;

    vector<ll> count;
    REP(i, N) {
        count.push_back(leq[i] -
                        (i - distance(cnt.begin(), cnt.lower_bound(A[i]))));
        cnt.insert(A[i]);
    }

    print_v(count);

    ll ans = 0;

    for (auto v : count) {
        ans += mod_pow(2, v, mod);
        ans += mod - 1;
        ans %= mod;
    }

    cout << ans << endl;

    ll tmp = 0;
    map<ll, ll> dict;
    for (auto it = data.begin(); it != data.end(); ++it) {
        dict[*it] = tmp;
        tmp++;
    }

    REP(i, N) { A[i] = dict[A[i]]; }

    print_v(A);
}