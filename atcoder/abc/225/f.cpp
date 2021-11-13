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

ll mod = 1000000007;
ll N, K, i, j, k, l;
vector<string> S;

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    REP(i, N) {
        string s;
        cin >> s;
        S.push_back(s);
    }
    // sort(ALL(S));

    vector<string> ans;
    ans.push_back(S[0]);
    FOR(i, 1, N) {
        vector<pair<string, ll>> check;
        REP(j, i + 1) {
            string sub = "";
            REP(k, j) {
                sub += ans[k];
            }
            sub += S[i];
            FOR(k, j, i) {
                sub += ans[k];
            }
            // cout << sub << endl;
            check.push_back({sub, j});
        }
        sort(ALL(check));
        ans.insert(ans.begin() + check[0].second, S[i]);
    }
    REP(i, K) {
        cout << ans[i];
    }
    cout << endl;
}