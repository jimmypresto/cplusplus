#include <cstdio>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <set>

using namespace std;

//vector<int> sequence = { 0, 5, 2, 8, 6, 3, 6, 9, 7 };
vector<int> sequence = { 0, 10, 22, 9, 33, 21, 50, 41, 60, 80 }; 
#define V sequence.size()

vector<vector<int>> paths(V + 1, vector<int>(V + 1, 0));

vector<int> dp(V + 1, 0);

void CollectPath(int j, list<int>& path)
{
  if (j < 0) return;

  int maxDP = 0;
  int maxI = -1;
  for(int i = 0; i <= V; i++)
  {
    if(paths[i][j] > maxDP)
      maxI = i;
    maxDP = max(maxDP, paths[i][j]);
  }

  if(maxDP > 0)
  {
    path.push_front(j);
    CollectPath(maxI, path);
  }
  else if(j == 1)
  {
    path.push_front(j);
  }
}

void lis()
{
  dp[1] = 1;
  int maxDP = 0;

  for(int j = 1; j <= V; j++)
  {
    for(int i = 1; i < j; i++)
    {
      if(sequence[i] < sequence[j])
      {
        if(dp[j] < dp[i] + 1)
        {
          paths[i][j] = dp[i] + 1;
        }
        dp[j] = max(dp[i] + 1, dp[j]);
        maxDP = max(dp[j], maxDP);
      }
    }
  }
  printf("The longest increasing sequence is %d\n", maxDP);

  list<int> path;
  CollectPath(V - 1, path);
  for(auto i : path)
  {
    printf("%d ", sequence[i]);
  }
  printf("\n");
}

int main()
{
  lis();
  return 0;
}
