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

const ll mod = 998244353;
ll N, K, M, Q, i, j, k, l;
vector<ll> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }

    // 二分探索は lb, ub の前提条件(条件を満たす or not)
    // と range error に注意する必要がある

    ll tmp = 0;
    REP(i, N) tmp += A[i];
    K = min(K, tmp);

    // 条件を満たす最大値を求める
    ll lb = 0;            // これは条件を満たす必要がある
    ll ub = 10000000000;  // これは条件を満たさない必要がある
    while (ub - lb > 1) {
        ll mid = (ub + lb) / 2;  // mid は ub の初期値にはならない
        ll tmp = 0;
        REP(i, N) { tmp += max(0LL, A[i] - mid); }
        if (tmp >= K) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    ll ans = 0;
    REP(i, N) {
        ll count = max(0LL, A[i] - lb - 1);
        ans += count * (A[i] + lb + 2) / 2;
        K -= count;
    }
    cout << ans + K * (lb + 1) << endl;
}