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
ll compress(vector<ll> &vec) {
    map<ll, ll> memo;                      // key: 変換前, value: 変換後
    for (const auto v : vec) memo[v] = 0;  // key 登録
    ll size = 0;
    for (auto &p : memo) p.second = size++;  // value 設定
    for (auto &v : vec) v = memo[v];         // value 設定
    return size;
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

// 動作確認: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6067217#1
ll inversions(vector<ll> &A) {
    ll n = compress(A);  // 座標圧縮
    BIT bit = BIT(n);
    ll ans = 0;
    REP(j, N) {
        // 既に i < j を満たす A[i] は bit に反映されている
        // i < j かつ A[i] <= A[j] を満たす i の個数を考える
        ans += bit.sum(A[j]);  // A[j] 以下の A[i] を考慮
        bit.add(A[j], 1);      // 個数なので足すのは 1
    }
    // i < j かつ A[i] > A[j] を満たす (i,j) の個数
    return N * (N - 1) / 2 - ans;
}

// i < j かつ A[i] <= A[j] となる (i,j) について
// A[j] - A[i] の総和
// Σ_i,j (A[j] - A[i])
// = Σ_j(A[j] * count_i - (Σ_i A[i]))
ll sum_relu(vector<ll> &A) {
    ll n = *max_element(A.begin(), A.end()) + 1;
    BIT bit_c = BIT(n);
    BIT bit_d = BIT(n);
    ll ans = 0;
    REP(j, N) {
        // 既に i < j を満たす A[i] は bit に反映されている
        // i < j かつ A[i] <= A[j] を満たす i の個数を考える
        ll pair_count = bit_c.sum(A[j]);  // ペアの個数
        bit_c.add(A[j], 1);
        ll pair_sum = bit_d.sum(A[j]);  // ΣA[i] (s.t. A[i] <= A[j])
        bit_d.add(A[j], A[j]);
        ans += pair_count * A[j] - pair_sum;
    }
    return ans;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }

    // cout << sum_relu(A) << endl;
    // cout << inversions(A) << endl;
}