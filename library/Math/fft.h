/*
 * "高速フーリエ変換"
 * last revised on: 2020/06/13
 * verified at: https://atcoder.jp/contests/atc001/tasks/fft_c
 */

#include "../template.h"

template <typename T>
void _fft_base(vector<complex<T>> &a, bool is_inv)
{
    const int n = a.size();
    assert((n & (n - 1)) == 0); // n が 2 のべき乗であることを確認
    const int h = __builtin_ctz(n);

    // 時間間引き
    for (int i = 0; i < n; i++) {
        int j = 0, ii = i, hh = h;
        while (hh) (j <<= 1) |= (ii & 1), ii >>= 1, hh--;
        if (i < j) swap(a[i], a[j]);
    }

    // バタフライ演算
    for (int b = 1; b < n; b <<= 1) {
        for (int i = 0; i < b; i++) {
            complex<T> w = polar(1., M_PI / b * i * (is_inv ? 1 : -1));
            for (int j = 0; j < n; j += (b << 1)) {
                complex<T> x = a[i + j];
                complex<T> y = a[i + j + b] * w;
                a[i + j] = x + y;
                a[i + j + b] = x - y;
            }
        }
    }

    if (is_inv) {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

template <typename T>
inline void fft(vector<complex<T>> &t) { return _fft_base(t, false); }

template <typename T>
inline void ifft(vector<complex<T>> &f) { return _fft_base(f, true); }

template <typename T>
vector<complex<T>> convolve(vector<complex<T>> a, vector<complex<T>> b)
{
    int n = a.size() + b.size() - 1;
    int m = 1 << (32 - __builtin_clz(2 * n - 1));
    a.resize(m), b.resize(m);
    fft(a), fft(b);
    for (int i = 0; i < m; i++) a[i] *= b[i];
    ifft(a);
    return a;
}
