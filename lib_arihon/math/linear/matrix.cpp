#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Real = long double;

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
}