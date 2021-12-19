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
template <typename T>
void print_sp(const set<T> data) {
    for (const auto v : data) {
        print_pair(v);
    }
    cout << endl;
}

const ll mod = 998244353;
ll N, M, Q, i, j, k, l;
vector<ll> A, B, C, D;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    A.resize(M);
    B.resize(M);
    REP(i, M) {
        cin >> j >> k;
        A[i] = j - 1;
        B[i] = k - 1;
    }
    C.resize(M);
    D.resize(M);
    REP(i, M) {
        cin >> j >> k;
        C[i] = j - 1;
        D[i] = k - 1;
    }
    set<pair<ll, ll>> user1;
    REP(i, M) { user1.insert({min(A[i], B[i]), max(A[i], B[i])}); }

    // print_sp(user1);

    vector<ll> v;
    REP(i, N) v.push_back(i);

    bool ans = false;

    do {
        set<pair<ll, ll>> user2;
        REP(i, M) {
            ll c = v[C[i]];
            ll d = v[D[i]];
            user2.insert({min(c, d), max(c, d)});
        }
        if (user1 == user2) ans = true;
    } while (next_permutation(v.begin(), v.end()));

    if (ans) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}