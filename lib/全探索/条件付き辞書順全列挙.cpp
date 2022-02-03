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

const ll mod = 998244353;  // 1000000007;
ll N, M, L, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;

    L = N;
    A.resize(L);
    REP(i, L) A[i] = i;  // 初期条件

    // ただの全列挙
    // 042531 の次は
    // - 1, 31, 531 は降順
    // - 2531 は降順ではない
    // - 2 を「531のうち2より大きい最小値」である3にする
    // 043XXX の XXX を昇順に 125 とする (043125)
    while (true) {
        REP(i, L) cout << A[i];
        cout << endl;

        // next
        ll tmp = A[L - 1];
        ll flg = -1;
        REP_R(i, L - 1) {
            if (tmp > A[i]) {
                flg = i;
                break;
            }
            tmp = A[i];
        }
        if (flg < 0) break;  // 全探索完了
        // 042531 のとき A[flg] は 2
        sort(next(A.begin(), flg + 1), A.end());  // 042531 -> 042135
        ll idx = distance(
            A.begin(), lower_bound(next(A.begin(), flg + 1), A.end(), A[flg]));
        swap(A[idx], A[flg]);  // 042135 -> 043521
    }
    cout << endl;

    // 2*N 個の要素で N 組のペアを作る
    L = 2 * N;
    A.resize(L);
    REP(i, L) A[i] = i;  // 初期条件
    // 制約: ペア内で left < right かつ left は昇順
    // 02/15/37/46 の次は
    // - right である 6, 76 は降順
    // - 576 は降順ではない
    // - 5 を「37/46のうち5より大きい最小値」である6にする
    // 02/16/XX/XX の XX/XX を昇順に 34/57 とする
    while (true) {
        REP(i, L) cout << A[i];
        cout << endl;

        // next
        ll tmp = A[L - 1];
        ll flg = -1;
        for (ll i = L - 1; i > 0; i -= 2) {
            if (tmp > A[i]) {  // 偶数番目(iは奇数)だけ見る
                flg = i;
                break;
            }
            tmp = A[i];
        }
        if (flg < 0) break;  // 全探索完了
        // 02/15/37/46 のとき A[flg] は 5
        sort(next(A.begin(), flg + 1), A.end());  // 02/15/37/46 -> 02/15/34/67
        ll idx = distance(
            A.begin(), lower_bound(next(A.begin(), flg + 1), A.end(), A[flg]));
        swap(A[idx], A[flg]);  // 02/15/37/46 -> 02/16/34/57
    }
}