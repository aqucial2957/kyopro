/*
 * "行列累乗ライブラリ"
 * last revised on: 2020/03/02
 * verified at: https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/10/ALDS1_10_A
 *              https://atcoder.jp/contests/dp/tasks/dp_r
 */

#include "../template.h"

template <typename T>
class Matrix
{
public:
    Matrix(int n, int m)
        : _value(n, vector<T>(m, 0)), _row(n), _col(m) {}
    Matrix(initializer_list<initializer_list<T>> init)
        : _value(init.begin(), init.end()), _row(init.size()), _col((*init.begin()).size()) {}

    int row(void) const { return _row; }
    int col(void) const { return _col; }

    vector<T> &operator[](size_t i) { return _value[i]; }
    const vector<T> &operator[](size_t i) const { return _value[i]; }

    // 単位行列E
    static Matrix E(int n)
    {
        Matrix res(n, n);
        for (int i = 0; i < n; i++) res[i][i] = 1;
        return res;
    }

    Matrix &operator+=(const Matrix &A)
    {
        int n = this->row(), m = this->col();
        assert(n == A.row() && m == A.col());

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                (*this)[i][j] += A[i][j];
            }
        } 
        return *this;
    }

    Matrix &operator-=(const Matrix &A)
    {
        int n = this->row(), m = this->col();
        assert(n == A.row() && m == A.col());

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                (*this)[i][j] -= A[i][j];
            }
        } 
        return *this;
    }

    Matrix &operator*=(const Matrix &A)
    {
        int n = this->row(), m = this->col(), l = A.col();
        assert(m == A.row());

        Matrix res(n, l);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < l; j++) {
                for (int k = 0; k < m; k++) {
                    res[i][j] += (*this)[i][k] * A[k][j];
                }
            }
        }
        return *this = move(res);
    }

    Matrix operator+(const Matrix &A) const { return Matrix(*this) += A; }
    Matrix operator-(const Matrix &A) const { return Matrix(*this) -= A; }
    Matrix operator*(const Matrix &A) const { return Matrix(*this) *= A; }

    Matrix pow(ll n) const
    {
        Matrix e = *this, res = E(this->row());
        while (n) {
            if (n & 1) res *= e;
            e *= e;
            n >>= 1;
        }
        return res;
    }

    friend ostream &operator<<(ostream &os, const Matrix &A)
    {
        int n = A.row(), m = A.col();
        for (int i = 0; i < n; i++) {
            os << "[";
            for (int j = 0; j < m; j++) {
                os << A[i][j];
                if (j < m - 1) os << ", ";
            }
            os << "]";
            if (i < n - 1) os << endl;
        }
        return os;
    }

private:
    vector<vector<T>> _value;
    size_t _row;
    size_t _col;
};
