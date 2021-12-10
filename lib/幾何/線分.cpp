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


class LineSegment {
   public:
    pair<ll, ll> from;
    pair<ll, ll> to;
    pair<ll, ll> vec;  // ベクトル
    ll l1dist;         // マンハッタン距離
    ll l2dist2;        // ユークリッド距離の2乗
    // (-90°,90°] の方向ベクトル
    // これが同じなら「直線の傾き」が同じ
    pair<ll, ll> b_vec;
    // b_len * b_vec = vec となる係数
    ll b_len;
    // b_vec か - b_vec のいずれか
    // これが同じなら「ベクトルの向き」が同じ
    pair<ll, ll> direction;
    // b_vec と (原点->from) の外積
    // b_vec と合わせて直線の一致判定が可能
    ll outer;

    LineSegment(pair<ll, ll> from_xy, pair<ll, ll> to_xy) {
        assert(from_xy != to_xy);
        from = from_xy;
        to = to_xy;
        ll dx = to.first - from.first;
        ll dy = to.second - from.second;

        vec = {dx, dy};
        l1dist = abs(dx) + abs(dy);
        l2dist2 = dx * dx + dy * dy;

        if (dx == 0) {
            b_vec = {0, 1};
            b_len = dy;
        } else if (dy == 0) {
            b_vec = {1, 0};
            b_len = dx;
        } else {
            ll adx = abs(dx);
            ll ady = abs(dy);
            ll g = __gcd(adx, ady);
            if (dx * dy > 0)
                b_vec = {adx / g, ady / g};
            else
                b_vec = {adx / g, -ady / g};
            b_len = vec.first / b_vec.first;
        }

        if (b_len > 0) {
            direction = b_vec;
        } else {
            direction = {-b_vec.first, -b_vec.second};
        }

        outer = b_vec.first * from.second - b_vec.second * from.first;
    }

    void print() {
        cout << "vec: " << vec.first << "," << vec.second << endl;
        cout << "l1: " << l1dist << ", l2^2: " << l2dist2 << endl;
        cout << "b_vec: " << b_vec.first << "," << b_vec.second << endl;
        cout << "b_len: " << b_len << endl;
    }
};

const ll mod = 998244353;
ll N, i;
string S;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    LineSegment ls1 = LineSegment({1, 2}, {5, -10});
    LineSegment ls2 = LineSegment({3, -4}, {2, -1});
    assert(ls1.b_vec == ls2.b_vec);
    assert(ls1.outer == ls2.outer);
}