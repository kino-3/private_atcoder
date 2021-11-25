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
            res += node[index]; // 加算
            index -= index & (-index);
        }
        return res;
    }

    // [left, right] の 和
    ll sum(ll left, ll right) {
        return sum(right) - sum(left - 1);
    }

    // index 番目に value を加える
    void add(ll index, ll value) {
        index++;
        while (index <= n) {
            node[index] += value; // 加算
            index += index & (-index);
        }
    }

    // index 番目を value とする
    void update(ll index, ll value) {
        ll cnt = sum(index, index);
        add(index, value - cnt);
    }
};

const ll mod = 998244353;
ll N, i;
string S;

int main() {
    BIT bit = BIT(5);
    bit.add(0, -1);
    bit.add(1, -10);
    bit.add(2, -100);
    bit.add(3, -1000);
    bit.add(4, -10000);
    assert(bit.sum(2, 2) == -100);
    assert(bit.sum(2) == -111);
    assert(bit.sum(1, 3) == -1110);
}