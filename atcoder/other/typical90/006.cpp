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

ll N, K;
string S;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    cin >> S;

    stack<char> ans;
    ll idx;
    REP(idx, N) {
        while (true) {
            if (ans.empty() || ans.size() + N - idx <= K) {
                ans.push(S[idx]);
                break;
            }
            if (ans.top() > S[idx]) {
                ans.pop();
                continue;
            } else if (ans.size() < K) {
                ans.push(S[idx]);
                break;
            } else {
                break;
            }
        }
    }
    vector<char> rev_ans;
    while (!ans.empty()) {
        rev_ans.push_back(ans.top());
        ans.pop();
    }
    reverse(ALL(rev_ans));
    REP(idx, K) { cout << rev_ans[idx]; }
    cout << endl;
}