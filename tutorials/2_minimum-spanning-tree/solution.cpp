#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
const int MAXM = 100000;

int pt[MAXN + 5];
pair<int,pair<int, int>> edges[MAXM + 5];
int N, M;

int root(int x) {
  if (x == pt[x]) {
    return x;
  }
  return pt[x] = root(pt[x]);
}

int main() {
  scanf("%d %d", &N, &M);
  for (int i = 0; i < N; ++i) {
    pt[i] = i;
  }
  for (int i = 0; i < M; ++i) {
    scanf("%d %d %d", &edges[i].second.first, &edges[i].second.second, &edges[i].first);
  }
  sort(edges, edges + M);
  int mst = 0;
  for (int i = 0; i < M; ++i) {
    int u = edges[i].second.first;
    int v = edges[i].second.second;
    if (root(u) != root(v)) {
      mst += edges[i].first;
      pt[root(u)] = root(v);
    }
  }
  printf("%d\n", mst);
}
