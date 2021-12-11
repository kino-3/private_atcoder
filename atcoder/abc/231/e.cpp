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
ll N, X, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> X;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }

    // Y に A[i] 以降のみ使う, A[i] は絶対使う
    ll ans = 0;
    map<ll, ll> res;
    res[X] = 0;
    REP_R(i, N) {
        vector<pair<ll, ll>> tmp;
        for (auto v : res) {
            tmp.push_back(v);
        }
        for (auto v : tmp) {
            ll mai = v.first / A[i];
            ll new1 = v.first - mai * A[i];
            ll new2 = (mai + 1) * A[i] - v.first;
            if (res.count(new1) > 0) {
                res[new1] = min(res[new1], v.second + mai);
            } else {
                res[new1] = v.second + mai;
            }
            if (res.count(new2) > 0) {
                res[new2] = min(res[new2], v.second + mai + 1);
            } else {
                res[new2] = v.second + mai + 1;
            }
        }
    }
    // REP(i, N) {
    //     ll cnt = 0;
    //     ll Y = 0;
    //     FOR_R(j, i, N) {
    //         while (Y + A[j] < X) {
    //             cnt++;
    //             Y += A[j];
    //         }
    //     }
    //     while (Y < X) {
    //         Y += A[i];
    //         cnt++;
    //     }
    //     Y -= X;
    //     debug_print(i, cnt, Y);
    //     ll t_cnt = 0;
    //     ll Z = 0;
    //     REP_R(j, i) {
    //         while (Z + A[j] <= Y) {
    //             cnt++;
    //             t_cnt ++;
    //             Z += A[j];
    //         }
    //     }
    //     debug_print(t_cnt, cnt);
    //     ans = min(ans, cnt);
    // }
    cout << res[0] << endl;
}