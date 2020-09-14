/*
 * "Ford-Fulkerson 法"
 * last revised on: 2020/03/10
 * verified at: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_A
 */

#include "../template.h"

class FordFulkerson
{
public:
    FordFulkerson(int n) : _n(n), _graph(n), _used(n, false) {}

    void add_edge(int from, int to, ll cap)
    {
        _graph[from].emplace_back(to, cap, (int)_graph[to].size());
        _graph[to].emplace_back(from, 0, (int)_graph[from].size() - 1);
    }

    ll operator()(int s, int t)
    {
        ll flow = 0;
        while (true) {
            fill(_used.begin(), _used.end(), false);
            ll f = dfs(s, t, linf);
            if (f == 0) return flow;
            flow += f;
        }
    }

private:
    struct edge
    {
        int to; ll cap; int rev;
        edge(int to, ll cap, int rev) : to(to), cap(cap), rev(rev) {}
    };

    int _n;
    vector<vector<edge>> _graph;
    vector<bool> _used;

    ll dfs(int v, int t, ll f)
    {
        if (v == t) return f;
        _used[v] = true;
        for (auto &e: _graph[v]) {
            if (!_used[e.to] && e.cap > 0) {
                ll d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    _graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
};
