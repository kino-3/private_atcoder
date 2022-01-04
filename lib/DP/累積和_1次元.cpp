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

// 1 次元累積和
class Ruiseki {
   public:
    vector<ll> accumulate;

    Ruiseki(vector<ll> base) {
        ll tmp = 0;
        for (auto v : base) {
            tmp += v;
            accumulate.push_back(tmp);
        }
    }

    // [left, right] の和
    ll sum(ll left, ll right) {
        assert(left <= right);
        assert(left >= 0);
        assert(right < accumulate.size());
        if (left == 0) {
            return accumulate[right];
        } else {
            return accumulate[right] - accumulate[left - 1];
        }
    }
};

const ll mod = 998244353;  // 1000000007;
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }
    Ruiseki ruiseki = Ruiseki(A);

    REP(i, A.size()) {
        FOR(j, i, A.size()) { cout << i << j << ruiseki.sum(i, j) << endl; }
    }
}