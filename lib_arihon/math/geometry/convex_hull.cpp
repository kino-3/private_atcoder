#include <bits/stdc++.h>
using namespace std;
using ll = long long;

typedef pair<ll, ll> P;

class ConvexHull {
    set<P> points;  // 重複は除いた全ての点

    // AB に対して, BC が時計回りにあるか
    bool is_clockwise(const P& a, const P& b, const P& c) {
        return (b.first - a.first) * (c.second - b.second) >
               (b.second - a.second) * (c.first - b.first);
    }

   public:
    ConvexHull() {}

    void add_point(P p) {
        points.insert(p);  // x -> y の優先度で昇順に並べられる
    }

    vector<P> exec() {
        vector<P> res(points.size() * 2);  // 構築中の凸包
        ll idx = 0;  // convex_full に格納された頂点数
        // 下側凸包の作成
        for (const auto& point : points) {
            while (idx > 1 &&
                   !is_clockwise(res[idx - 2], res[idx - 1], point)) {
                idx--;
            }
            res[idx] = point;
            idx++;
        }
        ll current_idx = idx;
        // 上側凸包の作成
        // 最初と最後の点は既に追加されているので, iter に入れない
        for (auto iter = next(points.rbegin()), e = prev(points.rend());
             iter != e; ++iter) {
            P point = *iter;
            while (idx > current_idx &&
                   !is_clockwise(res[idx - 2], res[idx - 1], point)) {
                idx--;
            }
            res[idx] = point;
            idx++;
        }
        res.resize(idx);
        return res;
    }
};

int main() {
    ConvexHull convex = ConvexHull();
    convex.add_point({6, 6});
    convex.add_point({3, 4});
    convex.add_point({8, 7});
    convex.add_point({1, 8});
    convex.add_point({0, 5});
    convex.add_point({6, 2});
    convex.add_point({8, 3});
    convex.add_point({5, 0});
    for (const auto& p : convex.exec()) {
        cout << p.first << "," << p.second << endl;
    }
}