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
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }

    // n 番目までの数列 ...(A) は相異なる
    // n + 1 番目までの数列は
    // ...(A)(B) (相異なる)
    // ...(A+B) (相異なる)
    // ...(A)(B) == ...(A+B) となるのは,
    // 「...(A) == ...(0)」のとき
    // ...(0) となる数列の個数は, 最も直近の和
    // が 0 となる区間を除いた ... の数列の個数

    vector<ll> dp;  // dp[i]: i 番目までの数列の個数(1-index)
    dp.push_back(0);
    dp.push_back(1);

    // 区間和 0
    map<ll, ll> accum;  // idx = [0, value) の区間和 が key
    // A[j]+...+A[i] == 0 となる j の最大値 (1-index)
    // j == 0 の場合や j が存在しない場合は 0
    // (...(0) の個数はどちらも 0 なので区別不要)
    vector<ll> zero;
    accum[0] = 0;
    ll tmp = 0;
    REP(i, N) {
        tmp += A[i];
        if (accum.count(tmp) > 0) {
            zero.push_back(accum[tmp]);
        } else {
            zero.push_back(0);
        }
        accum[tmp] = i + 1;
    }
    // print_v(zero);
    // print_map(accum);

    FOR(i, 1, N) { dp.push_back((dp[i] * 2 - dp[zero[i - 1]] + mod) % mod); }
    // print_v(dp);
    cout << dp[N] << endl;
}