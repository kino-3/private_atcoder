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

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

ll H, W, rs, cs, rt, ct, i, j, k, r, c;
ll INF = 100000000000;
string s;
vector<string> board;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W;
    vector<vector<ll>> count(H, vector<ll>(W, INF));
    cin >> rs >> cs;
    cin >> rt >> ct;
    rs -= 1;
    cs -= 1;
    rt -= 1;
    ct -= 1;
    REP(i, H) {
        cin >> s;
        board.push_back(s);
    }
    deque<pair<ll, ll>> que;
    que.push_back({rs, cs});
    count[rs][cs] = -1;
    while (!que.empty()) {
        auto P = que.front();
        que.pop_front();
        ll step = count[P.first][P.second] + 1;
        r = P.first + 1;
        c = P.second;
        while (r < H && board[r][c] == '.') {
            if (step < count[r][c]) {
                count[r][c] = step;
                que.push_back({r, c});
            }
            r += 1;
        }
        r = P.first - 1;
        c = P.second;
        while (r >= 0 && board[r][c] == '.') {
            if (step < count[r][c]) {
                count[r][c] = step;
                que.push_back({r, c});
            }
            r -= 1;
        }
        r = P.first;
        c = P.second + 1;
        while (c < W && board[r][c] == '.') {
            if (step < count[r][c]) {
                count[r][c] = step;
                que.push_back({r, c});
            }
            c += 1;
        }
        r = P.first;
        c = P.second - 1;
        while (c >= 0 && board[r][c] == '.') {
            if (step < count[r][c]) {
                count[r][c] = step;
                que.push_back({r, c});
            }
            c -= 1;
        }
    }
    count[rs][cs] = 0;
    cout << count[rt][ct] << endl;
}