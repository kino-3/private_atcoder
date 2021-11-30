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

const ll mod = 998244353;
ll N, M, i, j, k, l;
vector<vector<bool>> good;

map<pair<ll, ll>, ll> seq;
map<pair<pair<ll, ll>, pair<ll, ll>>, ll> div2;

ll find_div(ll l1, ll r1, ll l2, ll r2) {
    if (div2.count({{l1, r1}, {l2, r2}})) return div2[{{l1, r1}, {l2, r2}}];
    ll idx1, idx2;
    ll res = 0;
    FOR(idx1, l1, r1) {
        FOR(idx2, l2, r2) {
            if (good[idx1][idx2]) {
                
            }
        }
    }
}

ll find_seq(ll l, ll r) {
    if (l == r) return 1;
    if (r - l == 1 || r - l == 3) return 0;
    if (seq.count({l, r}) > 0) return seq[{l, r}];
    if (r - l == 2) return (good[l][l + 1] ? 1 : 0);
    ll res = 0;
    if (good[l][l + 1]) res += find_seq(l + 2, r);
    if (good[r - 2][r - 1]) res += find_seq(l, r - 2);
    ll idx;
    FOR(idx, l + 1, r - 2) {
        if (good[idx][idx + 1]) {
            res += find_div(l, idx, idx + 2, r);
        }
    }
    res %= mod;
    seq[{l, r}] = res;
    return res;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    good.resize(N, vector<bool>(N, false));
    REP(i, M) {
        cin >> j >> k;
        good[j - 1][k - 1] = true;
        good[k - 1][j - 1] = true;
    }
    cout << find_seq(0, N) << endl;
}