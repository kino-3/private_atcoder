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

// 2 次元累積和
// 動作確認: https://atcoder.jp/contests/abc203/tasks/abc203_d
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

const ll mod = 998244353;
ll N, M, i, j, k, l;
vector<vector<ll>> A, dp, rev_dp;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // N 行 M 列の行列の受け取り
    cin >> N >> M;
    A.resize(N);
    REP(i, N) {
        REP(j, M) {
            cin >> k;
            A[i].push_back(k);
        }
    }
    // print_vv(A);

    Ruiseki ruiseki = Ruiseki(A);

    // 逆変換
    // rev_dp = dp;
    // FOR_R(i, 1, N) {
    //     REP(j, M) { rev_dp[i][j] -= rev_dp[i - 1][j]; }
    // }
    // REP(i, N) {
    //     FOR_R(j, 1, M) { rev_dp[i][j] -= rev_dp[i][j - 1]; }
    // }
    // print_vv(rev_dp);
}