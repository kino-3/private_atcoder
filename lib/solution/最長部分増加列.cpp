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
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

ll N, i, j, k;
vector<ll> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
    }

    // 最長部分増加列(LIS)
    // O(N log N)
    // https://atcoder.jp/contests/typical90/tasks/typical90_bh で検証済み
    vector<ll> dpl;  // dpl[idx] は idx 番目を最終要素とするLISの長さ
    vector<ll> dp;  // dp[idx] は現時点で長さ (idx+1) の LIS
                    // の末尾要素としてありうる最小値
    dp.push_back(A[0]);
    dpl.push_back(1);
    FOR(i, 1, N) {
        // A[i] までの情報を反映
        ll idx = distance(dp.begin(), lower_bound(ALL(dp), A[i]));
        if (idx == dp.size()) {
            dp.push_back(A[i]);
        } else {
            dp[idx] = A[i];
        }
        dpl.push_back(idx + 1);
    }
    // - dp.size(): LIS の長さ
    // - dpl を先頭から見て各valueのkeyの最小値を調べると,
    //   A[0:idx] のみを用いた LIS の長さがわかる。
}