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
ll N, M, Q, i, j, k, l, m;
vector<ll> sz;
vector<vector<pair<ll, ll>>> test;

// 0-indexed
class BIT {
   public:
    ll n;                                // 要素数
    vector<ll> node;                     // node[0] (=0) は使用しない
    BIT(ll n) : n(n), node(n + 1, 0) {}  // 配列は 0 で初期化する

    // [0, index] の index + 1 個の和
    ll sum(ll index) {
        index++;
        ll res = 0;
        while (index > 0) {
            res += node[index];  // 加算
            index -= index & (-index);
        }
        return res;
    }

    // [left, right] の 和
    ll sum(ll left, ll right) { return sum(right) - sum(left - 1); }

    // index 番目に value を加える
    void add(ll index, ll value) {
        index++;
        while (index <= n) {
            node[index] += value;  // 加算
            index += index & (-index);
        }
    }

    // index 番目を value とする
    void update(ll index, ll value) {
        ll cnt = sum(index, index);
        add(index, value - cnt);
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    sz.resize(N);
    test.resize(N);
    REP(i, N) {
        cin >> m;
        sz[i] = m;
        REP(j, m) {
            cin >> k >> l;
            test[i].push_back({l, k});
        }
    }

    REP(i, N) {
        bool ans = true;

        sort(ALL(test[i]));
        BIT bit = BIT(1000000002);
        debug_print_count();
        for (auto v : test[i]) {
            if (bit.sum(v.second, v.first) == v.first - v.second + 1) {
                ans = false;
                break;
            }
            // できるだけ左にいれる
            // 条件を満たす最小値を求める
            ll lb = v.second - 1;  // これは条件を満たさない必要がある
            ll ub = v.first;  // これは条件を満たす必要がある
            while (ub - lb > 1) {
                ll mid = (ub + lb) / 2;  // mid は lb の初期値にはならない
                if (bit.sum(mid, v.second) > mid - v.second + 1) {
                    ub = mid;
                } else {
                    lb = mid;
                }
                debug_print(i, lb, ub);
            }
            bit.add(ub, 1);
        }
        if (ans) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}