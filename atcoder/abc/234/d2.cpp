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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

const ll mod = 998244353;  // 1000000007;
ll N, K, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }

    tree<ll, null_type, greater<ll>, rb_tree_tag,
         tree_order_statistics_node_update>
        pbds_set;
    REP(i, K - 1) { pbds_set.insert(A[i]); }
    FOR(i, K - 1, N) {
        pbds_set.insert(A[i]);
        cout << *(pbds_set.find_by_order(K - 1)) << endl;
    }
}