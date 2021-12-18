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
ll N, K, i, j, k, l;
string S;
vector<vector<bool>> A;
vector<pair<ll, ll>> direction = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

// bool is_field(pair<ll, ll> pos) {
//     if (pos.first < 0) return false;
//     if (pos.first >= N) return false;
//     if (pos.second < 0) return false;
//     if (pos.second >= N) return false;
//     return A[pos.first][pos.second];
// }

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;

    A.resize(N);

    REP(i, N) {
        cin >> S;
        REP(j, N) { A[i].push_back(S[j] == '.'); }
    }

    // https://atcoder.jp/contests/abc211/tasks/abc211_e
    // K マスの連結の全探索 (K == 10 位が限界な気がする)
    pair<ll, ll> base = {0, 0};   // {0, 0} を始点とする
    set<set<pair<ll, ll>>> data;  // i マスの全探索の結果
    set<pair<ll, ll>> tmp;
    tmp.insert(base);
    data.insert(tmp);  // 1 マスの場合

    REP(i, K - 1) {
        // i + 2 マスで構成される場合を考える
        set<set<pair<ll, ll>>> new_data;
        for (auto v : data) {
            for (auto vv : v) {
                for (auto d : direction) {
                    // i + 1 マスの結果にマス cnt を加える
                    pair<ll, ll> cnt = {d.first + vv.first,
                                        d.second + vv.second};
                    if (v.count(cnt) > 0)
                        continue;  // i + 1 マスが cnt を含んでいた場合

                    // 新しい i+2 マスのパターンは制約を満たすか
                    // 今回はマス base よりもマス cnt が大きい場合を除く
                    // (始点を動かしてさらに全探索をする場合を考慮)
                    if (base < cnt) continue;

                    // 既に含まれてい
                    auto newv = v;
                    newv.insert(cnt);
                    new_data.insert(newv);
                }
            }
        }
        data = new_data;
    }
    // cout << data.size() << endl;
}