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

const ll mod = 1000000007;
ll N, M, Q, i, j, k, l;
vector<ll> A, ruiseki;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }
    ll tmp = 0;
    REP(i, N) {
        tmp += A[i];
        ruiseki.push_back(tmp);
    }

    // print_v(ruiseki);

    // 前計算
    // prev[i][j]: ruiseki[i] ≡ ruiseki[k] (mod j) and (k < j) となる最大の k
    vector<vector<ll>> prev(N, vector<ll>(N + 1, -1));
    FOR(i, 1, N + 1) {
        // amari[k]: i で割った余りが k である直近の場所
        vector<ll> amari(N, -1);
        REP(j, N) {
            ll cnt = ruiseki[j] % i;
            if (amari[cnt] >= 0) {
                prev[j][i] = amari[cnt];
            }
            amari[cnt] = j;
        }
    }

    // assert(false);
    // print_map(prev[4]);

    vector<map<ll, ll>> dp(N);
    REP(i, N) dp[i][1] = 1;

    FOR(i, 1, N) {
        FOR(j, 1, N + 1) {
            ll pos = prev[i][j];
            if (pos == -1) continue;
            ll tmp = 0;
            if (dp[pos].count(j)) tmp += dp[pos][j];
            if (dp[pos].count(j - 1)) tmp += dp[pos][j - 1];
            dp[i][j] = tmp;
        }
    }

    ll ans = 0;
    for (auto v : dp[N - 1]) {
        ans += v.second;
        ans %= mod;
    }
    cout << ans << endl;
}