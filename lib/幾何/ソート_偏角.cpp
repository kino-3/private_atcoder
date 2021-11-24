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

// see: ./atcoder/abc/225/e.cpp

ll mod = 1000000007;
ll N, i, x, y, l;
vector<tuple<ll, ll, ll>> point;  // x, y, idx

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // 原点を除いた (x, y) の sort
    cin >> N;
    vector<tuple<ll, ll, ll>> point_tmp;
    REP(i, N) {
        cin >> x >> y;
        if (y > 0 || (y == 0 && x > 0)) {
            point.push_back({x, y, i});  // [0, 180)
        } else {
            point_tmp.push_back({x, y, i});  // [180, 360)
        }
    }
    sort(point.begin(), point.end(), [](const auto& l, const auto& r) {
        ll xl = get<0>(l);
        ll yl = get<1>(l);
        ll xr = get<0>(r);
        ll yr = get<1>(r);
        return xl * yr - xr * yl > 0;
    });
    sort(point_tmp.begin(), point_tmp.end(), [](const auto& l, const auto& r) {
        ll xl = get<0>(l);
        ll yl = get<1>(l);
        ll xr = get<0>(r);
        ll yr = get<1>(r);
        return xl * yr - xr * yl > 0;
    });
    copy(point_tmp.begin(), point_tmp.end(), std::back_inserter(point));
    // 180 度までなら
    // REP(i, N) {
    //     cin >> x >> y;
    //     point.push_back({x, y, i});
    // }
    // sort(point.begin(), point.end(), [](const auto& l, const auto& r) {
    //     ll xl = get<0>(l);
    //     ll yl = get<0>(l);
    //     ll xr = get<0>(r);
    //     ll yr = get<0>(r);
    //     return xl * yr - xr * yl > 0;
    // });
    REP(i, N) {
        cout << get<0>(point[i]) << get<1>(point[i]) << get<2>(point[i])
             << endl;
    }
}