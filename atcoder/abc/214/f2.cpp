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

const ll mod = 1000000007;
ll N, M, i, j, k, l;
string S, T;

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

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> S;
    N = S.size();
    vector<ll> dp(N);

    // 一見 O(|S|^2) だが, 各文字で REP_R は同じ
    // ところを一回ずつしか走査しないから O(26|S|)
    // 累積和でも処理できる
    REP(i, N) {
        dp[i] = 1;  // i 文字目のみ
        REP_R(j, i) {
            if (S[j] == S[i]) {
                dp[i] = 0;  // 既出
                break;
            }
        }
        if (i > 1 && S[i] == S[i - 1]) {
            // ...abb の新しい文字列は
            // ...a に b を足したもののみ
            // (... に b を足したものは
            // ...ab で既出)
            dp[i] = dp[i - 2];
        } else {
            // ...xa___a の文字列のうち, 既出のものは
            // ... の文字列
            // (...xa は未出)
            for (ll j = i - 2; j >= 0; j--) {
                dp[i] += dp[j];
                dp[i] %= mod;
                if (S[i] == S[j+1]) break;
            }
        }
    }
    // print_v(dp);
    ll ans = 0;
    REP(i, N) {
        ans += dp[i];
        ans %= mod;
    }
    cout << ans << endl;
}