#include <bits/stdc++.h>

#include <atcoder/all>
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

const ll mod = 998244353;  // 1000000007;
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    B.resize(N);
    REP(i, N) {
        cin >> A[i];
        cin >> B[i];
    }

    // 実装は NTT らしい
    // convolution_ll は 戻り値が ll に収まっている必要があるが,
    // mod * mod が ll に収まっても Σ (mod * mod) は ll
    // に収まらないことがあるので 使わないほうが良い気がする。
    // ref.
    // https://atcoder.github.io/ac-library/production/document_ja/convolution.html
    vector<ll> res = atcoder::convolution(A, B);
    for (auto v : res) {
        cout << v << " ";
    }

    // REP(i, N) cin >> A[i];
    // REP(i, N) cin >> B[i];
    // REP(i, N) {
    //     A[i]--;
    //     B[i]--;
    // }
}