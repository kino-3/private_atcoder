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


// 凸包
// 動作確認
// - https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6095106#1
class ConvexHull {
    set<pair<ll, ll>> points;  // 重複は除いた全ての点

    // AB に対して, BC が時計回りにあるか
    // 不等号 > を >= にすれば, 線分上も含む
    // (動作確認:
    // https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6095106#1)
    bool is_clockwise(const pair<ll, ll>& a, const pair<ll, ll>& b,
                      const pair<ll, ll>& c) {
        return (b.first - a.first) * (c.second - b.second) >
               (b.second - a.second) * (c.first - b.first);
    }

   public:
    //  x が最小の点のうち, y が最小の点を始点として, 反時計周り
    // o
    // o <- 始点
    //  o
    vector<pair<ll, ll>> convex_points;
    // 候補が複数ある場合は反時計回り
    vector<ll> left;  // 最も左の点の idx
    vector<ll> right;
    vector<ll> upper;
    vector<ll> lower;

    ConvexHull() {}

    void add_point(pair<ll, ll> p) {
        points.insert(p);  // x -> y の優先度で昇順に並べられる
    }

    // 凸包(convex_points), 特徴点 の結果を格納する
    void exec() {
        assert(points.size() > 1);
        vector<pair<ll, ll>> res;  // 形成中の凸包
        // 下側凸包の作成
        for (const auto& point : points) {
            ll sz = res.size();
            while (sz > 1 && !is_clockwise(res[sz - 2], res[sz - 1], point)) {
                res.pop_back();
                sz = res.size();
            }
            res.push_back(point);
        }
        ll lsz = res.size();
        // 上側凸包の作成
        // 最後の点(右端上)は既に追加されているので iter に入れない
        for (auto iter = next(points.rbegin()); iter != points.rend(); ++iter) {
            pair<ll, ll> point = *iter;
            ll sz = res.size();
            while (sz > lsz && !is_clockwise(res[sz - 2], res[sz - 1], point)) {
                res.pop_back();
                sz = res.size();
            }
            res.push_back(point);
        }
        res.pop_back();  // 始点と終点が重複するので終点を除く
        convex_points = res;  // 結果

        // 特徴点を調べる
        ll idx = 0;
        left.push_back(idx);
        ll end = res.size() - 1;
        if (res[end].first == res[0].first) {
            left.push_back(end);
        }

        while (res[idx].second > res[idx + 1].second) idx++;
        lower.push_back(idx);
        if (res[idx].second == res[idx + 1].second) {
            lower.push_back(idx + 1);
            idx++;
        }

        while (res[idx].first < res[idx + 1].first) idx++;
        right.push_back(idx);
        if (res[idx].first == res[idx + 1].first) {
            right.push_back(idx + 1);
            idx++;
        }

        while (res[idx].second < res[idx + 1].second) idx++;
        upper.push_back(idx);
        if (res[idx].second == res[idx + 1].second) {
            upper.push_back(idx + 1);
            idx++;
        }
    }
};

const ll mod = 998244353;
ll N, M, Q, i, j, k, l;
vector<ll> X, Y;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    X.resize(N);
    Y.resize(N);
    REP(i, N) { cin >> X[i] >> Y[i]; }

    ConvexHull convex = ConvexHull();
    REP(i, N) convex.add_point({X[i], Y[i]});
    convex.exec();
    // for (auto p : convex.convex_points) print_pair(p);
    // print_v(convex.left);
    // print_v(convex.right);
    // print_v(convex.lower);
    // print_v(convex.upper);
}