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
ll N, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    ll size = 0;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
        size += j;
    }
    if (size % 10 != 0) {
        cout << "No" << endl;
    } else {
        size /= 10;
        ll left = 0;
        ll right = 0;
        REP(i, N) { A.push_back(A[i]); }
        ll tmp = A[0];
        while (left < N) {
            if (tmp == size) {
                cout << "Yes" << endl;
                break;
            } else if (tmp < size) {
                right++;
                tmp += A[right];
            } else {
                tmp -= A[left];
                left++;
            }
        }
        if (left >= N) {
            cout << "No" << endl;
        }
    }
}