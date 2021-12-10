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
ll N, M, i, j, k, l;
string S;
vector<vector<bool>> A;

template <typename T>
vector<vector<T>> expand(vector<vector<T>> field) {
    T fill_value = false;  // TODO
    ll R = field.size();
    ll C = field[0].size();
    vector<vector<T>> res(R + 2, vector<T>(C + 2, fill_value));
    for (ll i = 0; i < field.size(); i++) {
        copy(field[i].begin(), field[i].end(), res[i + 1].begin() + 1);
    }
    return res;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;

    A.resize(N);
    REP(i, N) {
        cin >> S;
        REP(j, M) { A[i].push_back(S[j] == '.'); }
    }
    // A.resize(N);
    // REP(i, N) {
    //     REP(j, M) {
    //         cin >> k;
    //         A[i].push_back(k == 1);
    //     }
    // }
}