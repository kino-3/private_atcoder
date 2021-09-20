#include <bits/stdc++.h>
using namespace std;
using Real = long double;
using Point = complex<Real>;
const Real EPS = 1e-10;

// OA と OB の内積
Real dot(const Point& a, const Point& b) {
    return real(a) * real(b) + imag(a) * imag(b);
}

// OA と OB の外積
Real cross(const Point& a, const Point& b) {
    return real(a) * imag(b) - imag(a) * real(b);
}

enum ccw_type {
    COUNTER_CLOCKWISE,
    CLOCKWISE,
    ONLINE_BACK,   // CAB の並び
    ONLINE_FRONT,  // ABC の並び
    ON_SEGMENT,    // 線分上(両端含む)
};

// 線分 AB に対して, 点 C がどこにあるか
ccw_type ccw(const Point& a, Point b, Point c) {
    b = b - a;
    c = c - a;
    if (cross(b, c) > EPS) return COUNTER_CLOCKWISE;
    if (cross(b, c) < -EPS) return CLOCKWISE;
    if (dot(b, c) < -EPS) return ONLINE_BACK;
    if (norm(c) - norm(b) > EPS) return ONLINE_FRONT;
    return ON_SEGMENT;
}

int main() {
    cout << dot({1, 2}, {3, 4}) << endl;
    cout << cross({1, 2}, {3, 4}) << endl;
    cout << (ccw({1, 1}, {2, 1}, {0, 2}) == COUNTER_CLOCKWISE) << endl;
    cout << (ccw({1, 1}, {2, 1}, {3, 0}) == CLOCKWISE) << endl;
    cout << (ccw({1, 1}, {2, 2}, {0, 0}) == ONLINE_BACK) << endl;
    cout << (ccw({1, 1}, {2, 2}, {3, 3}) == ONLINE_FRONT) << endl;
    cout << (ccw({1, 1}, {2, 2}, {1.5, 1.5}) == ON_SEGMENT) << endl;
}