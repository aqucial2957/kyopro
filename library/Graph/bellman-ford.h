#include "../template.h"

// copy from here

struct edge
{
    int from, to; ll cost;
    edge(int from, int to, ll cost) : from(from), to(to), cost(cost) {}
};

vector<ll> bellman_ford(const vector<edge> &es, int v, int s)
{
    vector<ll> dst(v, linf);
    dst[s] = 0;

    for (int i = 0; i < v; i++) {
        for (auto &e: es) {
            if (dst[e.from] != linf && dst[e.to] > dst[e.from] + e.cost) {
                dst[e.to] = dst[e.from] + e.cost;
                if (i == v - 1) return vector<ll> ();
            }
        }
    }
    return dst;
}