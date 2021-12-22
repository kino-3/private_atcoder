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

const ll mod = 998244353;
ll N, M, C, i, j, k, l;
vector<vector<ll>> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // N 行 M 列の行列の受け取り
    cin >> N >> M >> C;
    A.resize(N);
    REP(i, N) {
        REP(j, M) {
            cin >> k;
            A[i].push_back(k);
        }
    }
    ll ans = numeric_limits<ll>::max();

    auto B = deep_copy_2d(A);
    {
        REP(i, N) {
            REP(j, M) { B[i][j] -= C * (i + j); }
        }
        // print_vv(B);
        vector<vector<ll>> cost(N, vector<ll>(M));
        REP(i, N) {
            REP(j, M) {
                if (i > 0)
                    ans = min(A[i][j] + C * (i + j) + cost[i - 1][j], ans);
                if (j > 0)
                    ans = min(A[i][j] + C * (i + j) + cost[i][j - 1], ans);
                cost[i][j] = B[i][j];
                if (i > 0) cost[i][j] = min(cost[i][j], cost[i - 1][j]);
                if (j > 0) cost[i][j] = min(cost[i][j], cost[i][j - 1]);
            }
        }
        // print_vv(cost);
    }

    // 逆
    REP(i, N) {
        REP(j, M) { B[i][j] = A[i][M - j - 1]; }
    }
    REP(i, N) {
        REP(j, M) { A[i][j] = B[i][j]; }
    }
    REP(i, N) {
        REP(j, M) { B[i][j] -= C * (i + j); }
    }
    // print_vv(B);
    vector<vector<ll>> cost(N, vector<ll>(M));
    REP(i, N) {
        REP(j, M) {
            if (i > 0)
                ans = min(A[i][j] + C * (i + j) + cost[i - 1][j], ans);
            if (j > 0)
                ans = min(A[i][j] + C * (i + j) + cost[i][j - 1], ans);
            cost[i][j] = B[i][j];
            if (i > 0) cost[i][j] = min(cost[i][j], cost[i - 1][j]);
            if (j > 0) cost[i][j] = min(cost[i][j], cost[i][j - 1]);
        }
    }
    // print_vv(cost);
    cout << ans << endl;
}