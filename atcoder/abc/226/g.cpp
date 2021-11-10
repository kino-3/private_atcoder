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
ll T, i, j, k, l;
vector<vector<ll>> A, B;

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

    cin >> T;
    REP(i, T) {
        A.push_back(vector<ll>(0));
        B.push_back(vector<ll>(0));
        REP(j, 5) {
            cin >> k;
            A[i].push_back(k);
        }
        REP(j, 5) {
            cin >> k;
            B[i].push_back(k);
        }
    }
    REP(i, T) {
        auto bag = A[i];
        auto man = B[i];
        REP_R(j, 5) {         // の荷物 43210
            FOR_R(k, j, 5) {  // の人
                ll count = min(man[k], bag[j]);
                bag[j] -= count;
                man[k] -= count;
                if (k - j > 0) {
                    man[k - j - 1] += count;
                }
            }
        }
        bool poss = true;
        REP(j, 5) {
            if (bag[j] > 0) poss = false;
        }
        if (poss) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}