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
string S;
vector<ll> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    cin >> S;
    REP(i, N) { A.push_back(S[i] - 'A'); }
    vector<vector<ll>> dp(
        1024, vector<ll>(10, 0));  // dp[S][j]: ?????? S ???????????? j ???????????????
    REP(i, N) {
        // ????????? A[i] ???????????????????????????????????????
        ll state;
        REP(state, 1 << 10) {
            std::bitset<10> bs(state);  // ??????
            if (bs[A[i]]) {
                std::bitset<10> bs2(state);
                bs2.reset(A[i]);
                ll rstate = int(bs2.to_ulong());
                dp[state][A[i]] *= 2;  // ???????????????
                REP(j, 10) { dp[state][A[i]] += dp[rstate][j]; }
                dp[state][A[i]] %= mod;
            }
        }
        std::bitset<10> bs(0);  // ??????
        bs.set(A[i]);
        state = int(bs.to_ulong());
        dp[state][A[i]]++;
    }
    ll ans = 0;
    REP(i, 1 << 10) {
        REP(j, 10) {
            ans += dp[i][j];
            ans %= mod;
        }
    }
    cout << ans << endl;
}