/*
 * "セグメント木"
 * last revised on: 2020/03/03
 * verified at: https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A
 *              https://atcoder.jp/contests/abc125/tasks/abc125_c
 */

#include "../template.h"

/*
 * セグメント木を 1-indexed で管理する．
 *            1
 *      2           3
 *   4     5     6     7
 *  8  9 10 11 12 13 14 15
 * ........................
 * 
 * ノード i に対し，
 *   親ノード : i / 2 (= i >> 1)
 *   子ノード : i * 2, i * 2 + 1
 */

// copy from here

template <typename T>
class SegmentTree
{
public:
    SegmentTree(const int n, const T &unit) : _unit(unit)
    {
        _n = 1 << __lg(2 * n - 1);
        _data.resize(2 * _n, unit);
    }

    SegmentTree(const vector<T> &v, const T &unit) : _unit(unit)
    {
        int n = v.size();
        _n = 1 << __lg(2 * n - 1);
        _data.resize(2 * _n, unit);

        // 最下段に要素をセット
        for (int i = 0; i < n; i++) this->set(i, v[i]);
        // セグメント木を構築
        this->build();
    }

    // k 番目の要素を最下段にセット
    void set(int k, const T &x) { _data[k + _n] = x; }

    // セグメント木を構築
    void build(void) 
    {
        for (int i = _n - 1; i > 0; i--) _data[i] = f(_data[2 * i], _data[2 * i + 1]);
    }

    // k番目の値をxに更新する
    void update(int k, const T &x)
    {
        k += _n; // 葉の節点に変換
        _data[k] = x;
        while (k >>= 1) _data[k] = f(_data[2 * k], _data[2 * k + 1]);
    }

    // 区間[a, b)に対してクエリ処理した結果を返す
    T query(int a, int b)
    {
        T left = _unit, right = _unit;
        a += _n, b += _n; // 葉の節点に変換
        for (; a < b; a >>= 1, b >>= 1) {
            if (a & 1) left  = f(left, _data[a++]);
            if (b & 1) right = f(_data[--b], right);
        }
        return f(left, right);
    }

    const T &operator[](size_t k) const { return _data[k + _n]; }
    T &operator[](size_t k) { return _data[k + _n]; }

private:
    int _n;          // 要素数
    vector<T> _data; // データを格納する配列
    T _unit;        // 単位元

    // クエリ処理用の関数
    T f(const T &a, const T &b) { return min(a, b); }
};
