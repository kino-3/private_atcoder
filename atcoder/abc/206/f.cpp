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

const ll mod = 998244353;
ll T, M, i, j, k, l;
vector<ll> N;
vector<vector<ll>> L, R;
vector<ll> LL, RR;
ll NN;
vector<vector<ll>> memo;

ll grundy(ll left, ll right) {
    if (memo[left][right] != -1) return memo[left][right];
    if (left == right) return 0;
    set<ll> g;
    REP(i, NN) {
        if (left <= LL[i] && RR[i] <= right) {
            g.insert(grundy(left, LL[i]) ^ grundy(RR[i], right));
        }
    }
    ll res = 0;
    while (g.count(res) > 0) res++;
    memo[left][right] = res;
    return res;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // N 行 M 列の行列の受け取り
    cin >> T;
    L.resize(T);
    R.resize(T);
    N.resize(T);
    REP(i, T) {
        cin >> N[i];
        M = N[i];
        REP(j, M) {
            cin >> k >> l;
            L[i].push_back(k - 1);
            R[i].push_back(l - 1);
        }
    }
    // print_vv(R);

    REP(i, T) {
        NN = N[i];
        LL = L[i];
        RR = R[i];
        memo = vector<vector<ll>>(100, vector<ll>(100, -1));
        if (grundy(0, 99) == 0) {
            cout << "Bob" << endl;
        } else {
            cout << "Alice" << endl;
        }
    }
}