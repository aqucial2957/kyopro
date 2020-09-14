/*
 * "重み付き Union-Find 木"
 * last revised on: 2020/03/02
 * verified at: https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B
 *              https://atcoder.jp/contests/arc090/tasks/arc090_b
 */

#include "../template.h"

template<typename T = int>
class WeightedUnionFind
{
public:
    WeightedUnionFind(int n = 0, T unity = 0) : _data(n, -1), _weight(n, unity), _count(n) {}

    int find(int x)
    {
        if (_data[x] < 0) return x;

        int root = find(_data[x]);
        _weight[x] += _weight[_data[x]];
        return _data[x] = root;
    }

    T weight(int x)
    {
        find(x);
        return _weight[x];
    }

    bool unite(int x, int y, T w)
    {
        w += weight(x), w -= weight(y);
        x = find(x), y = find(y);
        if (x == y) return false;

        if (_data[x] > _data[y]) {
            swap(x, y);
            w = -w;
        }
        _data[x] += _data[y];
        _data[y] = x;
        _weight[y] = w;
        _count--;
        return true;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    T diff(int x, int y) { return weight(y) - weight(x); }

    int size(int x) { return -_data[find(x)]; }

    int count(void) const { return _count; }

private:
    vector<int> _data;
    vector<T>   _weight;
    int _count; 
};
