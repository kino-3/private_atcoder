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

ll N, K, i, j, k;
vector<ll> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
    }

    ll begin = 0;
    ll end = 0;
    map<ll, ll> counter;
    while (end < N) {
        if (counter.count(A[end]) > 0) {
            counter[A[end]] ++;
        } else {
            counter[A[end]] = 1;
        }
        if (counter.size() > K) {
            counter.erase(A[end]);
            break;
        }
        end += 1;
    }
    ll ans = end - begin;
    while (end < N) {
        while (true) {
            if (counter[A[begin]] > 1) {
                counter[A[begin]] --;
            } else {
                counter.erase(A[begin]);
                begin ++;
                break;
            }
            begin ++;
        }
        while (end < N) {
            if (counter.count(A[end]) > 0) {
                counter[A[end]] ++;
            } else {
                counter[A[end]] = 1;
            }
            if (counter.size() > K) {
                counter.erase(A[end]);
                break;
            }
            end += 1;
        }
        ans = max(ans, end - begin);
    }
    cout << ans << endl;
}