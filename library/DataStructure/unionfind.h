/*
 * "Union-Find 木"
 * last revised on: 2020/03/02
 * verified at: https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_A
 *              https://atcoder.jp/contests/atc001/tasks/unionfind_a
 */

#include "../template.h"

class UnionFind
{
public:
    UnionFind(int n = 0) : _data(n, -1), _count(n) {}

    int find(int x)
    {
        if (_data[x] < 0) return x;
        else return _data[x] = find(_data[x]);
    }

    bool unite(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y) return false;

        if (_data[x] > _data[y]) swap(x, y);
        _data[x] += _data[y];
        _data[y] = x;
        _count--;
        return true;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    int size(int x) { return -_data[find(x)]; }

    int count(void) const { return _count; }

private:
    vector<int> _data;
    int _count;
};
