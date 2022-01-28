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
string S, T;
vector<ll> A0, B0, A1, B1;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> S >> T;
    A0.resize(S.size());
    A1.resize(S.size());
    B0.resize(T.size());
    B1.resize(T.size());
    REP(i, S.size()) {
        A0[i] = (S[i] == '0' ? 1LL : 0LL);
        A1[i] = (S[i] == '1' ? 1LL : 0LL);
    }
    REP(i, T.size()) {
        B0[i] = (T[i] == '0' ? 1LL : 0LL);
        B1[i] = (T[i] == '1' ? 1LL : 0LL);
    }
    reverse(ALL(B0));
    reverse(ALL(B1));

    vector<ll> res0 = atcoder::convolution_ll(A0, B0);
    vector<ll> res1 = atcoder::convolution_ll(A1, B1);
    
    ll same = 0;
    FOR(i, T.size() - 1, S.size()) {
        same = max(same, res0[i] + res1[i]);
    }
    cout << T.size() - same << endl;
}