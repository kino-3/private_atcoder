#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Real = long double;
const Real EPS = 1e-10;

// 行列積は O(n^3)
// m 乗は O(n^3 log m)
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
        // 正方行列の n 乗
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
        // 正方行列の n 乗
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

    // Gauss Jordan 法で matrix を破壊的に変換する
    // rank を返す
    // 拡大係数行列 (is_extended = true) の場合は最終列は変換しない
    int gauss_jordan_real(bool is_extended = false) {
        int rank = 0;
        // matrix の要素が Real ではない場合はここでエラーを吐く
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

    // (正則な正方行列であれば)逆行列を返す
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
        if (rank < col) return M;  // 正則ではない
        vector<vector<Real>> res(row, vector<Real>(col, 0.0));
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                res[r][c] = M.matrix[r][c + col];
            }
        }
        return Matrix<Real>(res);
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

int main() {
    Matrix<int> m = Matrix<int>({{0, 1}, {2, 3}, {4, 5}});
    m.print();
    Matrix<int> m2 = Matrix<int>({{0, 1, 2}, {3, 4, 5}});
    m.mul(m2).print();
    m.mul_mod(m2, 3).print();
    Matrix<int> m3 = Matrix<int>({{2, 0}, {0, 3}});
    m3.pow(6).print();
    m3.pow_mod(6, 20).print();
    Matrix<Real> m4 = Matrix<Real>({{0, 1, 2}, {3, 4, 5}});
    m4.gauss_jordan_real();
    m4.print();
    Matrix<Real> m5 = Matrix<Real>({{3, 1, 1}, {5, 1, 3}, {2, 0, 1}});
    m5.inverse().print();
}