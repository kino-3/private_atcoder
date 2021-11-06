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

ll N, K, i, j, k, l;
vector<ll> X, Y;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    REP(i, N) {
        cin >> j >> k;
        X.push_back(j);
        Y.push_back(k);
    }
    // ここから解説参照

    // スコアの計算(ビット全探索)
    vector<ll> A_max;
    vector<ll> A_min;
    vector<ll> score;
    REP(i, 1 << N) {  // i = 0...2^N-1 (N 桁の辞書順)
        if (i == 0) {
            // 空集合のスコアを仮定義
            A_max.push_back(numeric_limits<ll>::min());
            A_min.push_back(numeric_limits<ll>::max());
            score.push_back(0);
        }
        std::bitset<100> bs(i);
        REP_R(j, N) {     // 上位桁からループ
            if (bs[j]) {  // 最上位は j 桁目
                // j 桁目と j 桁目以外に分けて DP の要領で計算
                // 000101101 = i のスコアは
                // 000100000 = (1 << j) のスコアと
                // 000001101 = other のスコアで決まる
                ll other = i - (1 << j);
                A_max.push_back(max(A[j], A_max[other]));
                A_min.push_back(min(A[j], A_min[other]));
                score.push_back(A_max[i] - A_min[i]);
                break;
            }
        }
    }
    // print_v(score);

    // 全体スコアの計算(ビットDP)
    // total_score[i][sub]: sub を i+1 個以下の集合に分割したときの total_score
    vector<vector<ll>> total_score(K, vector<ll>(1 << N));
    REP(k, K) {
        if (k == 0) {
            REP(i, 1 << N) {
                // 分割無しのときはスコアそのもの
                total_score[k][i] = score[i];
            }
        } else {
            // 部分集合 i を k 以下分割するときの i での total_score
            REP(i, 1 << N) {
                ll tmp_score = numeric_limits<ll>::max();
                ll sup = i;
                ll sub = i;
                do {  // 辞書順にループ
                    // sub と (i - sub の k-1 以下分割) に分割
                    ll tmp = max(total_score[k - 1][sub], score[sup - sub]);
                    tmp_score = min(tmp, tmp_score);
                    // cout << sup << " " << sub << " " << tmp << endl;
                    sub = (sub - 1) & sup;  // see. 蟻本 p.144
                } while (sub != sup);
                total_score[k][i] = tmp_score;
            }
        }
        // print_v(total_score[k]);
    }
    cout << total_score[K - 1][(1 << N) - 1] << endl;
}