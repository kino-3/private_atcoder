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
void debug_print(const T item) {
    cout << item << endl;
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 10);
}
template <typename T>
void print_v(const vector<T> vec) {
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}
template <typename T>
void print_vv(const vector<T> vec) {
    for (auto &&item : vec) {
        print_v(item);
    }
}
template <typename K, typename V>
void print_map(const map<K, V> dict) {
    for (const auto v : dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v : data) {
        cout << v << ", ";
    }
    cout << endl;
}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {
    cout << "(" << data.first << "," << data.second << ")";
    // cout << endl;
}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {
    cout << "(";
    cout << get<0>(data) << "," << get<1>(data) << "," << get<2>(data);
    cout << ")";
    // cout << endl;
}

const ll mod = 998244353;
ll N, M, i, j, k, l;
string S;
vector<vector<bool>> A, B;

template <typename T>
vector<vector<T>> expand(vector<vector<T>> field) {
    T fill_value = false;  // TODO
    ll R = field.size();
    ll C = field[0].size();
    vector<vector<T>> res(R + 2, vector<T>(C + 2, fill_value));
    for (ll i = 0; i < field.size(); i++) {
        copy(field[i].begin(), field[i].end(), res[i + 1].begin() + 1);
    }
    return res;
}

pair<ll, ll> find_lu(vector<vector<bool>> m) {
    REP(i, N) {
        REP(j, N) {
            if (m[i][j]) {
                return {i, j};
            }
        }
    }
    return {0, 0};
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;

    A.resize(N);
    B.resize(N);
    REP(i, N) {
        cin >> S;
        REP(j, N) { A[i].push_back(S[j] == '#'); }
    }
    REP(i, N) {
        cin >> S;
        REP(j, N) { B[i].push_back(S[j] == '#'); }
    }
    vector<vector<bool>> Bl(N, vector<bool>(N));
    vector<vector<bool>> Br(N, vector<bool>(N));

    REP(i, N) {
        REP(j, N) {
            Bl[i][j] = B[N - j - 1][i];
            Br[i][j] = B[j][N - i - 1];
        }
    }

    // print_vv(Bl);
    // print_vv(Br);

    bool ans = false;

    pair<ll, ll> ap = find_lu(A);
    pair<ll, ll> bp = find_lu(B);
    pair<ll, ll> blp = find_lu(Bl);
    pair<ll, ll> brp = find_lu(Br);

    bool tmpans;
    ll i_e, j_e;
    tmpans = true;
    i_e = min(N - ap.first, N - bp.first);
    j_e = min(N - ap.second, N - bp.second);
    REP(i, i_e) {
        REP(j, j_e) {
            if (A[i + ap.first][j + ap.second] !=
                B[i + bp.first][j + bp.second])
                tmpans = false;
        }
    }
    ans = ans || tmpans;

    tmpans = true;
    i_e = min(N - ap.first, N - blp.first);
    j_e = min(N - ap.second, N - blp.second);
    REP(i, i_e) {
        REP(j, j_e) {
            if (A[i + ap.first][j + ap.second] !=
                Bl[i + blp.first][j + blp.second])
                tmpans = false;
        }
    }
    ans = ans || tmpans;

    tmpans = true;
    i_e = min(N - ap.first, N - brp.first);
    j_e = min(N - ap.second, N - brp.second);
    REP(i, i_e) {
        REP(j, j_e) {
            if (A[i + ap.first][j + ap.second] !=
                Br[i + brp.first][j + brp.second])
                tmpans = false;
        }
    }
    ans = ans || tmpans;

    if (ans) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}