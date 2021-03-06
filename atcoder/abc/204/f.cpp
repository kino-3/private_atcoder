#include <bits/stdc++.h>
#define REP(var, n) for (decltype(n) var = 0; var < (n); var++)
#define REP_R(var, n) \
    for (auto var = (n)-1; var != static_cast<decltype(var)>(-1); var--)
#define FOR(var, a, b) for (auto var = (a); var < (b); var++)
#define FOR_R(var, a, b) for (auto var = (b - 1); var > (a - 1); var--)
#define ALL(c) std::begin(c), std::end(c)

using namespace std;
using ll = long long;
using Real = long double;
const Real EPS = 1e-10;

// REP(idx, 3) { cout << idx; }  // 012
// REP_R(idx, 3) { cout << idx; }  // 210
// FOR(idx, 4, 7) { cout << idx; }  // 456
// FOR_R(idx, 4, 7) { cout << idx; }  // 654
// sort(ALL(v));

void debug_print() { cout << endl; }
template <class Head, class... Tail>
void debug_print(Head &&head, Tail &&...tail) {
    std::cout << head << ", ";
    debug_print(std::forward<Tail>(tail)...);
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
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {
    for (auto &&item : vec) {
        print_pair(item);
    }
}

class UnionFind {
   public:
    // ?????????????????? -(????????????)
    // ??????????????????????????????
    // ??????????????????
    std::vector<ll> data;

    UnionFind(ll size) : data(size, -1) {}

    // ?????????????????????
    // ???????????????????????????(?????????????????????????????????????????????????????????false)
    bool unite(ll x, ll y) {
        x = root(x);
        y = root(y);
        if (x != y) {
            if (data[y] < data[x]) std::swap(x, y);
            // ????????????????????????(x)???y???????????????
            data[x] += data[y];
            data[y] = x;
        }
        return x != y;
    }

    // ????????????????????????
    bool find(ll x, ll y) { return root(x) == root(y); }

    // ???????????????????????????
    // (????????????????????????????????????????????????????????????)
    ll root(ll x) { return (data[x] < 0) ? x : data[x] = root(data[x]); }

    // ???????????????????????????
    ll size(ll x) { return -data[root(x)]; }
};

// ???????????? O(n^3)
// m ?????? O(n^3 log m)
template <class T>
class Matrix {
   public:
    vector<vector<T>> matrix;
    int row;
    int col;

    Matrix(vector<vector<T>> matrix)
        : matrix(matrix), row(matrix.size()), col(matrix.at(0).size()) {}

    Matrix mul(Matrix m) {
        vector<vector<T>> res(row, vector<T>(m.col, 0));
        for (int l = 0; l < row; l++) {
            for (int r = 0; r < m.col; r++) {
                T sum = 0;
                for (int k = 0; k < col; k++) {
                    sum += matrix[l][k] * m.matrix[k][r];
                }
                res[l][r] = sum;
            }
        }
        return Matrix(res);
    }

    Matrix mul_mod(Matrix m, ll mod) {
        vector<vector<T>> res(row, vector<T>(m.col, 0));
        for (int l = 0; l < row; l++) {
            for (int r = 0; r < m.col; r++) {
                T sum = 0;
                for (int k = 0; k < col; k++) {
                    sum += (matrix[l][k] * m.matrix[k][r]) % mod;
                }
                res[l][r] = sum % mod;
            }
        }
        return Matrix(res);
    }

    Matrix pow(ll n) {
        // ??????????????? n ???
        vector<vector<T>> identity;
        for (int i = 0; i < row; i++) {
            vector<T> v(col, 0);
            v[i] = 1;
            identity.push_back(v);
        }
        Matrix res = Matrix(identity);
        Matrix m = Matrix(matrix);
        while (n > 0) {
            if (n & 1) {
                res = res.mul(m);
            }
            m = m.mul(m);
            n >>= 1;
        }
        return res;
    }

    Matrix pow_mod(ll n, ll mod) {
        // ??????????????? n ???
        vector<vector<T>> identity;
        for (int i = 0; i < row; i++) {
            vector<T> v(col, 0);
            v[i] = 1;
            identity.push_back(v);
        }
        Matrix res = Matrix(identity);
        Matrix m = Matrix(matrix);
        while (n > 0) {
            if (n & 1) {
                res = res.mul_mod(m, mod);
            }
            m = m.mul_mod(m, mod);
            n >>= 1;
        }
        return res;
    }

    // Gauss Jordan ?????? matrix ???????????????????????????
    // rank ?????????
    // ?????????????????? (is_extended = true) ???????????????????????????????????????
    int gauss_jordan_real(bool is_extended = false) {
        int rank = 0;
        // matrix ???????????? Real ????????????????????????????????????????????????
        vector<vector<Real>>& M = matrix;
        for (int c = 0; c < col; c++) {
            if (is_extended && c == col - 1) break;
            int pivot_row = -1;
            Real pivot_value = EPS;
            for (int r = rank; r < row; r++) {
                if (abs(M[r][c]) > pivot_value) {
                    pivot_value = M[r][c];
                    pivot_row = r;
                }
            }
            if (pivot_row == -1) continue;
            swap(M[pivot_row], M[rank]);
            for (int c2 = 0; c2 < col; c2++) {
                M[rank][c2] /= pivot_value;
            }
            for (int r = 0; r < row; r++) {
                if (r != rank && abs(M[r][c]) > EPS) {
                    Real v = M[r][c];
                    for (int c2 = 0; c2 < col; c2++) {
                        M[r][c2] -= M[rank][c2] * v;
                    }
                }
            }
            rank++;
        }
        return rank;
    }

    // (?????????????????????????????????)??????????????????
    Matrix<Real> inverse() {
        assert(row == col);
        vector<vector<Real>> extended_matrix;
        for (int r = 0; r < row; r++) {
            vector<Real> v(col * 2, 0.0);
            copy(matrix[r].begin(), matrix[r].end(), v.begin());
            v[col + r] = 1.0;
            extended_matrix.push_back(v);
        }
        auto M = Matrix<Real>(extended_matrix);
        int rank = M.gauss_jordan_real();
        if (rank < col) return M;  // ??????????????????
        vector<vector<Real>> res(row, vector<Real>(col, 0.0));
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                res[r][c] = M.matrix[r][c + col];
            }
        }
        return Matrix<Real>(res);
    }

    // Ax=b ???????????????
    // ?????????????????????1???????????????
    // ????????????????????? size ??? 0 ??? vector ?????????
    vector<Real> solve(vector<Real> b) {
        assert(row == b.size());
        Matrix<Real> Ab = this->deepcopy();
        for (int r = 0; r < row; r++) {
            Ab.matrix[r].push_back(b[r]);
            Ab.col += 1;
        }
        int rank = Ab.gauss_jordan_real(true);
        vector<Real> x;
        for (int r = rank; r < row; r++) {
            if (abs(Ab.matrix[r][col]) > EPS) return x;  // ?????????
        }
        int r = 0;
        for (int i = 0; i < rank; i++) {
            while (abs(Ab.matrix[i][r]) < EPS) {
                x.push_back(0.0);  // ?????????????????????
                r++;
            }
            x.push_back(Ab.matrix[i][col]);
            r++;
        }
        while (x.size() < col) {
            x.push_back(0.0);
        }
        return x;
    }

    Matrix<T> deepcopy() {
        vector<vector<T>> res(row, vector<T>(col, 0));
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                res[r][c] = matrix[r][c];
            }
        }
        return Matrix<T>(res);
    }

    void print() {
        cout << "(" << row << "," << col << ")" << endl;
        for (const auto& m_row : matrix) {
            cout << "{";
            for (const auto& value : m_row) {
                cout << value << ",";
            }
            cout << "}" << endl;
        }
        cout << endl;
    }
};

const ll mod = 998244353;
ll H, W, i, j, k, l;
string S, T;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W;

    vector<vector<ll>> trans(1 << H, vector<ll>(1 << H, -1));

    REP(i, 1 << H) {
        std::bitset<6> bsi(i);
        REP(j, 1 << H) {
            std::bitset<6> bsj(j);
            set<ll> free;
            REP(k, H) {
                if (bsi[k] && bsj[k]) {
                    trans[i][j] = 0;
                } else if (!bsi[k] && !bsj[k]) {
                    free.insert(k);
                }
            }
            if (trans[i][j] == 0) continue;
            UnionFind uf = UnionFind(H);
            REP(k, H - 1) {
                if (free.count(k) > 0 && free.count(k + 1) > 0) {
                    uf.unite(k, k + 1);
                }
            }
            ll idx = 0;
            ll tmp = 1;
            while (idx < H) {
                if (uf.size(idx) == 2) tmp *= 2;
                if (uf.size(idx) == 3) tmp *= 3;
                if (uf.size(idx) == 4) tmp *= 5;
                if (uf.size(idx) == 5) tmp *= 8;
                if (uf.size(idx) == 6) tmp *= 13;
                idx += uf.size(idx);
            }
            trans[i][j] = tmp;
        }
    }
    // print_vv(trans);
    Matrix<ll> matrix = Matrix<ll>(trans);
    auto res = matrix.pow_mod(W, mod);
    cout << res.matrix[0][0] << endl;
}