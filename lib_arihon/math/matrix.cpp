#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 行列積は O(n^3)
// m 乗は O(n^3 log m)
class Matrix {
   public:
    vector<vector<ll>> matrix;
    ll line;
    ll row;

    Matrix(vector<vector<ll>> matrix)
        : matrix(matrix), line(matrix.size()), row(matrix.at(0).size()) {}

    Matrix mul(Matrix m) {
        vector<vector<ll>> res(line, vector<ll>(m.row, 0));
        for (ll l = 0; l < line; l++) {
            for (ll r = 0; r < m.row; r++) {
                ll sum = 0;
                for (ll k = 0; k < row; k++) {
                    sum += matrix[l][k] * m.matrix[k][r];
                }
                res[l][r] = sum;
            }
        }
        return Matrix(res);
    }

    Matrix mul_mod(Matrix m, ll mod) {
        vector<vector<ll>> res(line, vector<ll>(m.row, 0));
        for (ll l = 0; l < line; l++) {
            for (ll r = 0; r < m.row; r++) {
                ll sum = 0;
                for (ll k = 0; k < row; k++) {
                    sum += (matrix[l][k] * m.matrix[k][r]) % mod;
                }
                res[l][r] = sum % mod;
            }
        }
        return Matrix(res);
    }

    Matrix pow(ll n) {
        // 正方行列の n 乗
        vector<vector<ll>> identity;
        for (int i = 0; i < line; i++) {
            vector<ll> v(row, 0);
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
        vector<vector<ll>> identity;
        for (int i = 0; i < line; i++) {
            vector<ll> v(row, 0);
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
        cout << "(" << line << "," << row << ")" << endl;
        for (const auto& m_line : matrix) {
            cout << "{";
            for (const auto& value : m_line) {
                cout << value << ",";
            }
            cout << "}" << endl;
        }
        cout << endl;
    }
};

int main() {
    Matrix m = Matrix({{0, 1}, {2, 3}, {4, 5}});
    m.print();
    Matrix m2 = Matrix({{0, 1, 2}, {3, 4, 5}});
    m.mul(m2).print();
    m.mul_mod(m2, 3).print();
    Matrix m3 = Matrix({{2, 0}, {0, 3}});
    m3.pow(6).print();
    m3.pow_mod(6, 20).print();
}