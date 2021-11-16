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

string S;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    S = "abc";
    string T = S;  // 値渡し
    string& U = S;
    S[0] = 5 + '0';      // 書き換え可能
    assert(S == "5bc");  // 文字列の値の比較
    assert(T == "abc");

    // pair の lower_bound
    // make_pair<ll, ll>(2, -10000) で型の指定が必要?
    vector<pair<ll, ll>> vec = {{1, 1}, {1, 2}, {1, 3}, {2, 1}, {2, 2}, {2, 3}};
    auto iter = lower_bound(vec.begin(), vec.end(), make_pair<ll, ll>(2, -10000));
    ll idx = distance(vec.begin(), iter);
    cout << idx << endl;
}