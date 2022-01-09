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

// https://codeforces.com/blog/entry/62393
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

const ll mod = 998244353;  // 1000000007;
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // policy based data structure
    // ref. https://xuzijian629.hatenablog.com/entry/2018/12/01/000010

    // set
    tree<ll, null_type, less<ll>, rb_tree_tag,
         tree_order_statistics_node_update>
        pbds_set;

    REP_R(i, 20) {
        pbds_set.insert(i);                            // insert は同じ
        if (pbds_set.find(i * 2) != pbds_set.end()) {  // find は同じ
            pbds_set.erase(i * 2);                     // erase は同じ
        }
    }
    for (auto v : pbds_set) cout << v << " ";  // 範囲 for は使える
    cout << endl;
    // ここからが追加
    REP(k, 5) {
        ll kth = *(pbds_set.find_by_order(k));  // k 番目の値へのイテレータ
        ll kless = pbds_set.order_of_key(k);  // k 未満の値の個数
        cout << k << ":" << kth << " " << kless << endl;
    }

    // unordered_map よりも早い
    gp_hash_table<ll, ll, custom_hash> safe_hash_table;
}