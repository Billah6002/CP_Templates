struct HopcroftKarp {
  const int INF = 1e9 + 7;
  vector <vector<int>> g;
  vector<int> match, dist;
  int nodes;

  void init(int _nodes) {
    nodes = _nodes;
    g.resize(_nodes);
    match.resize(_nodes);
    dist.resize(_nodes);
  }
  void add_edge(int u, int v) {
    g[u].push_back(v);
  }
  bool bfs(int n) {
    queue <int> q;
    for (int i = 1; i <= n; ++i) {
      if (!match[i]) dist[i] = 0, q.emplace(i);
      else dist[i] = INF;
    }
    dist[0] = INF;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (!u) continue;
      for (int v : g[u]) {
        if (dist[match[v]] == INF) {
          dist[match[v]] = dist[u] + 1, q.emplace(match[v]);
        }
      }
    }
    return dist[0] != INF;
  }
  bool dfs (int u) {
    if (!u) return 1;
    for (int v : g[u]) {
      if (dist[match[v]] == dist[u] + 1 and dfs(match[v])) {
        match[u] = v, match[v] = u;
        return 1;
      }
    }
    dist[u] = INF;
    return 0;
  }
  int hopcroftKarp() {
    int n = nodes - 1;
    int ret = 0;
    while (bfs(n)) {
      for (int i = 1; i <= n; ++i) {
        ret += !match[i] and dfs(i);
      }
    }
    return ret;
  }
};
