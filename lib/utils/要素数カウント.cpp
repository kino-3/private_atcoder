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


ll N, i, j, k;
vector<ll> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
    }

    map<ll, ll> counter;  // counter[key] は key の個数
    REP(i, A.size()) { counter[A[i]] += 1; }
    vector<ll> max_value;  // 最も多いやつ
    ll max_count = 0;
    for (auto it = counter.begin(), e = counter.end(); it != e; ++it) {
        if (max_count < it->second) {
            max_count = it->second;
            max_value.clear();
            max_value.push_back(it->first);
        } else if (max_count == it->second) {
            max_value.push_back(it->first);
        }
    }
    cout << max_count << endl;
    // print_v(max_value);
}