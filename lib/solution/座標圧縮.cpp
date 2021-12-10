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


const ll mod = 998244353;
ll N, i, j, k, l;
vector<ll> A, B;

// 破壊的に座標圧縮する
// vec の要素の種類数を返す
// 変換規則がほしい場合は memo を返せばよい
ll compress(vector<ll> &vec) {
    map<ll, ll> memo; // key: 変換前, value: 変換後
    for (const auto v: vec) memo[v] = 0; // key 登録
    ll size = 0;
    for (auto &p: memo) p.second = size++; // value 設定
    for (auto &v: vec) v = memo[v]; // value 設定
    return size;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    B.resize(N);
    REP(i, N) {
        cin >> A[i] >> B[i];
    }
    cout << compress(A) << endl;
    // print_v(A);
}