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
ll N, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }
    B.resize(N);
    REP(i, N) { cin >> B[i]; }

    ll same, diff;

    // c0 == c1 の場合
    same = A[0];
    diff = 10000000000000000;
    FOR(i, 1, N) {  // i = 1, ..., N-1
        ll tmp_same = min(same + B[i - 1], diff) + A[i];
        ll tmp_diff = min(same, diff + B[i - 1]);
        same = tmp_same;
        diff = tmp_diff;
    }
    same += B[N - 1];

    ll ans = min(same, diff);

    // c0 != c1 の場合
    same = 10000000000000000;
    diff = 0;
    FOR(i, 1, N) {  // i = 1, ..., N-1
        ll tmp_same = min(same + B[i - 1], diff) + A[i];
        ll tmp_diff = min(same, diff + B[i - 1]);
        same = tmp_same;
        diff = tmp_diff;
        // debug_print(same);
        // debug_print(diff);
        // debug_print_count();
    }
    diff += B[N - 1];

    ans = min(ans, min(same, diff));

    cout << ans << endl;
}