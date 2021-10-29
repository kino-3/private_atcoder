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

// 半分全列挙
// list1, list2 の要素で和が total となるものの個数
// 計算量は vector の sort
// ll count(const vector<ll>& list1, const vector<ll>& list2, ll total) {
//     vector<ll> list_1(list1.size());
//     vector<ll> list_2(list2.size());
//     copy(list1.begin(), list1.end(), list_1.begin());
//     copy(list2.begin(), list2.end(), list_2.begin());
//     sort(list_1.begin(), list_1.end());
//     sort(list_2.begin(), list_2.end(), greater<ll>());
//     ll ans = 0;
//     ll idx1 = 0;
//     ll idx2 = 0;
//     while (!(idx1 >= list_1.size() || idx2 >= list_2.size())) {
//         ll current_total = list_1[idx1] + list_2[idx2];
//         if (current_total > total) {
//             idx2 += 1;
//         } else if (current_total < total) {
//             idx1 += 1;
//         } else {
//             ll idx1init = idx1;
//             ll idx2init = idx2;
//             while (list_1[idx1] == list_1[idx1init]) {
//                 idx1 += 1;
//             }
//             while (list_2[idx2] == list_2[idx2init]) {
//                 idx2 += 1;
//             }
//             ans += (idx1 - idx1init) * (idx2 - idx2init);
//         }
//     }
//     return ans;
// }

// 半分全列挙
// list1, list2 の要素で和が total 以下となるものの個数
// 計算量は vector の sort
ll count(const vector<ll>& list1, const vector<ll>& list2, ll total) {
    vector<ll> list_1(list1.size());
    vector<ll> list_2(list2.size());
    copy(list1.begin(), list1.end(), list_1.begin());
    copy(list2.begin(), list2.end(), list_2.begin());
    sort(list_1.begin(), list_1.end());
    sort(list_2.begin(), list_2.end(), greater<ll>());
    ll ans = 0;
    ll idx = 0;
    for (const auto& v : list_1) {
        while (list_2[idx] + v > total) {
            idx++;
            if (idx == ll(list_2.size())) {
                return ans;
            }
        }
        ans += ll(list_2.size()) - idx;
    }
    return ans;
}

ll N, K, P, i, j, k, n;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K >> P;
    REP(i, N / 2) {
        cin >> j;
        A.push_back(j);
    }
    REP(i, N - N / 2) {
        cin >> j;
        B.push_back(j);
    }

    // 前半
    vector<vector<ll>> PA(K + 1);
    n = N / 2;
    FOR(k, 1, K + 1) {
        ll comb = (1 << k) - 1;
        ll end_comb = 1 << n;
        while (comb < end_comb) {
            std::bitset<100> bs(comb);
            ll ans = 0;
            REP_R(j, n) {
                if (bs[j]) ans += A[j];
            }
            if (ans <= P) {
                PA[k].push_back(ans);
            }
            // 後処理
            ll x = comb & -comb;
            ll y = comb + x;
            comb = ((comb & ~y) / x >> 1) | y;
        }
        PA[k].push_back(P + 1);
    }

    // 後半
    vector<vector<ll>> PB(K + 1);
    n = N - N / 2;
    FOR(k, 1, K + 1) {
        ll comb = (1 << k) - 1;
        ll end_comb = 1 << n;
        while (comb < end_comb) {
            std::bitset<100> bs(comb);
            ll ans = 0;
            REP_R(j, n) {
                if (bs[j]) ans += B[j];
            }
            if (ans <= P) {
                PB[k].push_back(ans);
            }
            // 後処理
            ll x = comb & -comb;
            ll y = comb + x;
            comb = ((comb & ~y) / x >> 1) | y;
        }
        PB[k].push_back(P + 1);
    }
    ll ans = 0;
    PA[0].push_back(0);
    PB[0].push_back(0);
    REP(k, K + 1) {
        if (PA[k].size() == 0 || PB[K - k].size() == 0) continue;
        ans += count(PA[k], PB[K - k], P);
    }
    cout << ans << endl;
}