#include "../template.h"

// copy from here

template <typename T, typename E = T>
class LazySegmentTree
{
public:
    LazySegmentTree(int n, const T &tunit, const E &eunit) : _tunit(tunit), _eunit(eunit)
    {
        _n = 1 << __lg(2 * n - 1);
        _data.resize(2 * _n - 1, tunit);
        _lazy.resize(2 * _n - 1, eunit);
    }

    void set(int k, const T &x) { _data[k + _n - 1] = x; }

    void build(void)
    {
        for (int i = _n - 2; i >= 0; i--) _data[i] = f(_data[2 * i + 1], _data[2 * i + 2]);
    }

    void update(int a, int b, const E &x) { return _update(a, b, x, 0, 0, _n); }

    T query(int a, int b) { return _query(a, b, 0, 0, _n); }

private:
    int _n;             // 要素数
    vector<T> _data;    // データを格納する配列
    vector<E> _lazy;    // 遅延評価するデータを格納する配列
    T _tunit;
    E _eunit;

    T f(const T &a, const T &b) { return min(a, b); }
    T g(const T &a, const E &b) { return b; }
    E h(const E &a, const E &b) { return b; }

    void eval(int k)
    {
        if (_lazy[k] == _eunit) return;
        if (k < _n - 1) {
            _lazy[2 * k + 1] = h(_lazy[2 * k + 1], _lazy[k]);
            _lazy[2 * k + 2] = h(_lazy[2 * k + 2], _lazy[k]);
        }
        _data[k] = g(_data[k], _lazy[k]);
        _lazy[k] = _eunit;
    }

    void _update(int a, int b, const E &x, int k, int l, int r)
    {
        eval(k);
        if (a <= l && r <= b) {
            _lazy[k] = h(_lazy[k], x); eval(k);
        } else if (a < r && l < b) {
            _update(a, b, x, 2 * k + 1, l, (l + r) >> 1);
            _update(a, b, x, 2 * k + 2, (l + r) >> 1, r);
            _data[k] = f(_data[2 * k + 1], _data[2 * k + 2]);
        }
    }

    T _query(int a, int b, int k, int l, int r)
    {
        eval(k);
        if (r <= a || b <= l) {
            return _tunit;
        } else if (a <= l && r <= b) {
            return _data[k];
        } else {
            T left = _query(a, b, k * 2 + 1, l, (l + r) >> 1);
            T right = _query(a, b, 2 * k + 2, (l + r) >> 1, r);
            return f(left, right);
        }
    }
};
