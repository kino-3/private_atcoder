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
ll N, Q, i, j, k, l;
vector<ll> T, X, Y;

template <typename T>
void print_v(const vector<T> vec) {
    for (auto &&item : vec) {
        cout << item + 1 << " ";
    }
    cout << endl;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> Q;
    vector<ll> prev(N, -1);
    vector<ll> next(N, -1);
    REP(i, Q) {
        cin >> j >> k;
        T.push_back(j);
        X.push_back(k - 1);
        if (j != 3) {
            cin >> l;
            Y.push_back(l - 1);
        } else {
            Y.push_back(0);
        }
    }

    REP(i, Q) {
        if (T[i] == 1) {
            prev[Y[i]] = X[i];
            next[X[i]] = Y[i];
        } else if (T[i] == 2) {
            prev[Y[i]] = -1;
            next[X[i]] = -1;
        } else {
            ll tmp = X[i];
            while (prev[tmp] != -1) {
                tmp = prev[tmp];
            }
            vector<ll> ans;
            while (tmp != -1) {
                ans.push_back(tmp);
                tmp = next[tmp];
            }
            cout << ans.size() << " ";
            print_v(ans);
        }
    }
}
