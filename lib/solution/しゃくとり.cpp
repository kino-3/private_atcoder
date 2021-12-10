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

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }

    // しゃくとりは片方を外側の for で 1 ずつ進めて,
    // もう片方を内側の while で条件を満たさなくなるまで進める

    // 条件を満たす最長を考えるときの尺取り
    // TODO: 最短を考える場合は right を 1 ずつ進めて, left
    // を条件を満たさなくなるまで進める
    ll right = 0;
    for (ll left = 0; left < N; left++) {
        while (cond(left, right)) {
            // [left, right] は条件を満たす
            cout << left << "," << right << endl;
            if (right == N - 1) {
                break;
            } else {
                right++;
            }
        }
        // 条件を満たさない場合と, right が末尾まで進んだ場合のいずれか
        // いずれにしても, 次は left を進める
    }
}