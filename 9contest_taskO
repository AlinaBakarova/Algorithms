#include <bits/stdc++.h>
using namespace std;

const int cN = 110;
const int cM = (1000 + 2 * cN) << 1;
const double cInf = 1e10;
const double cEps = 1e-8;

struct Edge {
  int var_u;
  int var_v;
} edges[cM];
int var_n;
int var_m;
int var_s;
int var_t;
int deg[cN];

struct Node {
  int to;
  int next;
  double var_c;
} e[cM];
int h[cN], tot;

void Add(int var_u, int var_v, double c1, double c2) {
  e[tot].to = var_v, e[tot].var_c = c1, e[tot].next = h[var_u],
  h[var_u] = tot++;
  e[tot].to = var_u, e[tot].var_c = c2, e[tot].next = h[var_v],
  h[var_v] = tot++;
}

void Build(double var_g) {
  memset(h, -1, sizeof h), tot = 0;
  for (int i = 1; i <= var_m; i++) {
    Add(edges[i].var_u, edges[i].var_v, 1, 1);
  }
  for (int i = 1; i <= var_n; i++) {
    Add(var_s, i, var_m, 0), Add(i, var_t, var_m + 2 * var_g - deg[i], 0);
  }
}

int qq[cN];
int dd[cN];
int cur[cN];
bool Bfs() {
  memset(dd, -1, sizeof dd);
  int tt = -1;
  int hh = 0;
  qq[++tt] = var_s, dd[var_s] = 0, cur[var_s] = h[var_s];

  while (tt >= hh) {
    int hd = qq[hh++];
    for (int i = h[hd]; (~i) != 0; i = e[i].next) {
      int go = e[i].to;
      if (dd[go] == -1 && e[i].var_c > cEps) {
        dd[go] = dd[hd] + 1;
        cur[go] = h[go];
        if (go == var_t) {
          return true;
        }
        qq[++tt] = go;
      }
    }
  }
  return false;
}

double Find(int var_u, double limit) {
  if (var_u == var_t) {
    return limit;
  }
  double flow = 0;
  for (int i = cur[var_u]; ((~i) != 0) && limit > flow; i = e[i].next) {
    int go = e[i].to;
    cur[var_u] = i;
    if (dd[go] == dd[var_u] + 1 && e[i].var_c > cEps) {
      double t = Find(go, min(limit - flow, e[i].var_c));
      if (t < cEps) {
        dd[go] = -1;
      }
      e[i].var_c -= t, e[i ^ 1].var_c += t, flow += t;
    }
  }
  return flow;
}

double Dinic(double var_g) {
  Build(var_g);
  double res = 0;
  double flow;
  while (Bfs()) {
    while ((flow = Find(var_s, cInf)) != 0.0) {
      res += flow;
    }
  }
  return res;
}

int res = 0;
bool vis[cN];
void Dfs(int var_u) {
  vis[var_u] = true;
  if (var_u != var_s) {
    res++;
  }
  for (int i = h[var_u]; (~i) != 0; i = e[i].next) {
    int go = e[i].to;
    if (e[i].var_c > 0 && !vis[go]) {
      Dfs(go);
    }
  }
}

int main() {
  cin >> var_n >> var_m;

  var_s = 0, var_t = var_n + 1;
  for (int i = 1; i <= var_m; i++) {
    int var_u;
    int var_v;
    cin >> var_u >> var_v;
    edges[i] = {var_u, var_v};
    deg[var_u]++, deg[var_v]++;
  }

  double var_l = 0;
  double var_r = var_m;
  while (var_l + cEps < var_r) {
    double mid = (var_l + var_r) / 2;
    if (var_m * var_n - Dinic(mid) > cEps) {
      var_l = mid;
    } else {
      var_r = mid;
    }
  }

  Dinic(var_l);
  Dfs(var_s);

  if (res == 0) {
    puts("1\n1");
    return 0;
  }

  cout << res << endl;
  for (int i = 1; i <= var_n; i++) {
    if (vis[i]) {
      cout << i << endl;
    }
  }

  return 0;
}
