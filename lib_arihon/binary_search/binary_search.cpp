#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
bool cond(T x) {
    return abs(x) < 3.141592;
}

ll search_max(ll lb, ll ub) {
    // 条件を満たす最大値を求める
    assert(lb < ub);
    assert(cond(lb));
    assert(!cond(ub));
    while (ub - lb > 1) {
        ll mid = (ub + lb) / 2;
        if (cond(mid)) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    return lb;
}

ll search_min(ll lb, ll ub) {
    // 条件を満たす最小値を求める
    assert(lb < ub);
    assert(!cond(lb));
    assert(cond(ub));
    while (ub - lb > 1) {
        ll mid = (ub + lb) / 2;
        if (cond(mid)) {
            ub = mid;
        } else {
            lb = mid;
        }
    }
    return ub;
}

double search_max(double lb, double ub, double eps) {
    // 条件を満たす最大値を求める
    assert(lb < ub);
    assert(cond(lb));
    assert(!cond(ub));
    while (ub - lb > eps) {
        double mid = (ub + lb) / 2;
        if (cond(mid)) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    return lb;
}

double search_min(double lb, double ub, double eps) {
    // 条件を満たす最小値を求める
    assert(lb < ub);
    assert(!cond(lb));
    assert(cond(ub));
    while (ub - lb > eps) {
        double mid = (ub + lb) / 2;
        if (cond(mid)) {
            ub = mid;
        } else {
            lb = mid;
        }
    }
    return ub;
}

int main() {
    cout << search_max(0, 100) << endl;
    cout << search_min(-100, 0) << endl;
    cout << search_max(0.1, 100, 1e-5) << endl;
    cout << search_min(-100, 0.1, 1e-5) << endl;
}