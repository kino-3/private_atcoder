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

const ll mod = 998244353;
ll H, W, N, i, j, k, l;
vector<ll> A, B;

// 破壊的に座標圧縮する
// vec の要素の種類数を返す
map<ll, ll> compress(vector<ll> &vec) {
    map<ll, ll> memo;                      // key: 変換前, value: 変換後
    for (const auto v : vec) memo[v] = 0;  // key 登録
    ll size = 0;
    for (auto &p : memo) p.second = size++;  // value 設定
    for (auto &v : vec) v = memo[v];         // value 設定
    return memo;
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

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W >> N;
    A.resize(N);
    B.resize(N);
    REP(i, N) { cin >> A[i] >> B[i]; }
    auto AA = deep_copy_1d(A);
    auto BB = deep_copy_1d(B);
    auto dict_A = compress(A);
    auto dict_B = compress(B);
    REP(i, N) { cout << dict_A[AA[i]] + 1 << " " << dict_B[BB[i]] + 1 << endl; }
}