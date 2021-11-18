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

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

ll mod = 998244353;
ll N, i, j, k, l;
vector<ll> A, B;
vector<ll> dp(3001, 0);
vector<ll> tmp_dp(3001, 0);

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
    }
    REP(i, N) {
        cin >> j;
        B.push_back(j);
    }
    dp[0] = 1;
    REP(i, N) {
        REP(j, A[i] + 1) {
            tmp_dp[A[i]] += dp[j];
            tmp_dp[A[i]] %= mod;
        }
        FOR(j, A[i] + 1, B[i] + 1) {
            tmp_dp[j] = tmp_dp[j - 1] + dp[j];
            tmp_dp[j] %= mod;
        }
        // print_v(tmp_dp);
        dp = tmp_dp;
        tmp_dp = deep_copy_1d(vector<ll>(3001, 0));
    }
    ll ans = 0;
    for (const auto v : dp) {
        ans += v;
        ans %= mod;
    }
    cout << ans << endl;
}