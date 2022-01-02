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

#ifdef _DEBUG
void debug_print() {
    cout << endl;
}
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {
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
    for (const auto v: dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v: data) {
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
#else
void debug_print() {}
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {}
void debug_print_count() {}
template <typename T>
void print_v(const vector<T> vec) {}
template <typename T>
void print_vv(const vector<T> vec) {}
template <typename K, typename V>
void print_map(const map<K, V> dict) {}
template <typename T>
void print_set(const set<T> data) {}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {}
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {}
#endif

const ll mod = 998244353;  // 1000000007;
ll N, K, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    A.resize(N);
    REP(i, N) {
        cin >> A[i];
    }
    sort(ALL(A));
    B = A;
    reverse(ALL(A));
    print_v(A);
    vector<ll> trans(N);
    REP(i, N) {
        ll cut = A[i] / 2 + 1;
        ll idx = distance(lower_bound(ALL(B), cut), B.end());
        trans[i] = idx;
    }
    print_v(trans);

    vector<vector<ll>> dp(32, vector<ll>(max(N, K + 1), -1));
    vector<vector<ll>> best(32, vector<ll>(max(N, K + 1), -1));

    REP(i, 32) {
        REP(k, K + 1) {
            if (i == 0) {
                dp[i][k] = k;
            } else {
                dp[i][k] = best[i - 1][k];
            }
        }
        REP(k, K + 1) {
            if (dp[i][k] >= N) {
                best[i][k] = N;
            } else {
                if (k == 0) {
                    best[i][k] = trans[dp[i][k]];
                } else {
                    best[i][k] = max(best[i][k - 1] + 1, trans[dp[i][k]]);
                }
            }
        }
        debug_print(i);
        print_v(dp[i]);
        print_v(best[i]);
        if (dp[i][K] >= N) {
            ll takahashi = i;
            ll aoki;
            REP(k, K + 1) {
                if (dp[i][k] >= N) {
                    aoki = k;
                    cout << takahashi << " " << aoki << endl;
                    return 0;
                }
            }
        }
    }
}