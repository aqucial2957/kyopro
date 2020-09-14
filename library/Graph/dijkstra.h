#include "../template.h"

struct edge
{
    int to; ll cost;
    edge(int to, ll cost) : to(to), cost(cost) {}
};

vector<ll> dijkstra(const vector<vector<edge>> &g, int s)
{
    using P = pair<ll, int>;

    priority_queue<P, vector<P>, greater<P>> q;
    vector<ll> dist(g.size(), linf);

    dist[s] = 0; q.emplace(0, s);
    while (!q.empty()) {
        auto [d, now] = q.top(); q.pop();
        if (dist[now] < d) continue;
        for (auto &e: g[now]) {
            if (dist[e.to] > d + e.cost) {
                dist[e.to] = d + e.cost;
                q.emplace(dist[e.to], e.to);
            }
        }
    }
    return move(dist);
}
