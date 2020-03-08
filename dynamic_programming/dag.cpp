#include <cstdio>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

#define V 6
enum VertexId
{
  S = 0, A, B, C, D, E
};
vector<vector<int>> adj(V, vector<int>(V, INT_MAX));
vector<list<VertexId>> ingress(V, list<VertexId>());
vector<list<VertexId>> egress(V, list<VertexId>());
vector<vector<int>> dp(V, vector<int>(V, INT_MAX));
const char Names[] = "SABCDE";

void addEdge(VertexId u, VertexId v, int weight)
{
  adj[u][v] = weight;
  dp[u][v] = weight;
  ingress[v].push_back(u);
  egress[u].push_back(v);
}

list<VertexId> getLinearOrder(VertexId s)
{
  list<VertexId> rets;

  queue<VertexId> q;
  q.push(s);

  while(!q.empty())
  {
    auto u = q.front();
    q.pop();

    rets.push_back(u);

    for(auto v : egress[u])
    {
      q.push(v);
    }   
  }
  return rets;
}

void dag()
{
  for(int s = S; s <= E; s++)
    dp[s][s] = 0;

  queue<VertexId> q;
  q.push(S);

  auto linearOrderVertice = getLinearOrder(S);

  while(!q.empty())
  {
    VertexId v = q.front();
    q.pop();

    for(auto s : linearOrderVertice)
    {
      for(auto u : ingress[v])
      {
        dp[s][v] = min(dp[s][u] + adj[u][v], dp[s][v]);
      }
    }

    for(auto n : egress[v])
    {
      q.push(n);
    }
  }
}

void dag2()
{
  for(int s = S; s <= E; s++)
    dp[s][s] = 0;

  list<VertexId> linearOrderVertice = getLinearOrder(S);

  for(auto v : linearOrderVertice)
  {
    for(auto s : linearOrderVertice)
    {
      for(auto u : ingress[v])
      {
        dp[s][v] = min(dp[s][u] + adj[u][v], dp[s][v]);
      }
    }
  }
}

void CollectPaths(VertexId s, VertexId v, stack<VertexId>& paths)
{
  paths.push(v);
  VertexId minU = v;
  int minDP = INT_MAX;
  for(auto u : ingress[v])
  {
    if(dp[s][u] < minDP)
    {
      minDP = dp[s][u];
      minU = u;

      if(minU == s)
      {
        paths.push(s);
        return;
      }
    }
  }

  CollectPaths(s, minU, paths);
}

int main()
{
  addEdge(S, A, 1);
  addEdge(S, C, 2);
  addEdge(A, B, 6);
  addEdge(B, D, 1);
  addEdge(B, E, 2);
  addEdge(C, A, 4);
  addEdge(C, D, 3);
  addEdge(D, E, 1);

  dag2();
  printf("Shortest path S to E: %d\n", dp[S][E]);

  stack<VertexId> paths;
  CollectPaths(S, E, paths);
  while(!paths.empty())
  {
    auto s = paths.top();
    paths.pop();
    printf("%c ", Names[s]);
  }
  printf("\n");

  return 0;
}
