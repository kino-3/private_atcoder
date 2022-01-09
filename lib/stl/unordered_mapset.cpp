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
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

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

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // map, set の操作は殆どが O(log N)
    // unordered_map, unordered_set の操作は殆どが平均 O(1)
    // 定数倍が遅い(らしい)
    // 非順序であることを除けば, map や set と同じ(はず)
    unordered_map<ll, ll, custom_hash> hash_map;
    unordered_set<ll, custom_hash> hash_set;

    FOR(i, 1000, 1010) {
        hash_set.insert(i * i * i);
        hash_map[i * i * i] = i;
    }
    for (auto v : hash_set) cout << v << " ";
    cout << endl;
    for (auto v : hash_map) cout << v.second << " ";
    cout << endl;
}