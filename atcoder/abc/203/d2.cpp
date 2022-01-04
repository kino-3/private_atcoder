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
ll N, M, K, i, j, k, l;
vector<vector<ll>> A;

// 2 次元累積和
class Ruiseki {
   public:
    vector<vector<ll>> accumulate;

    Ruiseki(vector<vector<ll>> base) {
        // dp[i][j] = A[i][j] + dp[i][j - 1] + dp[i - 1][j] - dp[i][j]
        // でもよいが, これだと D 次元で O(N^D 2^D) となる (各マスで2^D)
        // ref.
        // https://qiita.com/convexineq/items/afc84dfb9ee4ec4a67d5#2%E6%AC%A1%E5%85%83%E3%81%AE%E3%82%BC%E3%83%BC%E3%82%BF%E5%A4%89%E6%8F%9B
        FOR(i, 1, N) {
            REP(j, M) { base[i][j] += base[i - 1][j]; }
        }
        REP(i, N) {
            FOR(j, 1, M) { base[i][j] += base[i][j - 1]; }
        }
        ll d1 = base.size();
        ll d2 = base[0].size();
        accumulate = vector<vector<ll>>(d1 + 1, vector<ll>(d2 + 1, 0));
        for (ll p1 = 0; p1 < d1; p1++) {
            for (ll p2 = 0; p2 < d2; p2++) {
                accumulate[p1 + 1][p2 + 1] = base[p1][p2];
            }
        }
    }

    // 左上(pos1), 右下(pos2) の和(全て閉区間)
    ll sum(pair<ll, ll> pos1, pair<ll, ll> pos2) {
        ll p11 = accumulate[pos1.first][pos1.second];
        ll p12 = accumulate[pos1.first][pos2.second + 1];
        ll p21 = accumulate[pos2.first + 1][pos1.second];
        ll p22 = accumulate[pos2.first + 1][pos2.second + 1];
        return p22 - p21 - p12 + p11;
    }
};

bool cond(ll thresh) {
    // 中央値が thresh 以下になるものはあるか
    vector<vector<ll>> count(N, vector<ll>(N, 0));
    REP(i, N) {
        REP(j, N) {
            if (A[i][j] <= thresh) count[i][j] += 1;
        }
    }
    Ruiseki ruiseki = Ruiseki(count);
    bool exist = false;
    REP(i, N - K + 1) {
        REP(j, N - K + 1) {
            ll cnt = ruiseki.sum({i, j}, {i + K - 1, j + K - 1});
            if (cnt >= K * K - K * K / 2) {
                exist = true;
                break;
            }
        }
    }
    // print_vv(count);
    debug_print(thresh, exist);
    print_vv(count);
    return exist;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // N 行 M 列の行列の受け取り
    cin >> N >> K;
    M = N;
    A.resize(N);
    REP(i, N) {
        REP(j, M) {
            cin >> k;
            A[i].push_back(k);
        }
    }
    // print_vv(A);

    // 条件を満たす最小値を求める
    ll lb = -1;          // これは条件を満たさない必要がある
    ll ub = 1000000000;  // これは条件を満たす必要がある
    while (ub - lb > 1) {
        ll mid = (ub + lb) / 2;  // mid は lb の初期値にはならない
        if (cond(mid)) {
            ub = mid;
        } else {
            lb = mid;
        }
    }
    cout << ub << endl;
}