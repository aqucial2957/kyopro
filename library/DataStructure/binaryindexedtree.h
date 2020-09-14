#include "../template.h"

template <typename T>
class BIT
{
public:
    BIT(int size, T unity = 0) : bit(++size, unity), _unity(unity) {}

    // [a, b)の和を計算する
    T sum(int a, int b) { return _sum(b - 1) - _sum(a - 1); }

    // i番目の要素にxを加算
    void add(int i, T x) {
        for (++i; i < (int)bit.size(); i += i & -i) bit[i] += x;
    }

private:
    vector<T> bit;
    T _unity;

    T _sum(int i) {
        T s = _unity;
        for (++i; i > 0; i -= i & -i) s += bit[i];
        return s;
    }
};
