// Item Weight Value
//    1      6 $30
//    2      3 $14
//    3      4 $16
//    4      2 $9

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define V 4
int weights[] = { 0,  6,  3,  4, 2 };
int values[] =  { 0, 30, 14, 16, 9 };

int Kr(int tw, int n)
{
  if (n <= 0 || tw <= 0)
    return 0;

  int K = 0;
  for(int w = 1; w <= V; w++)
  {
    if(weights[w] > tw)
      continue;
    int v = values[w];
    K = std::max(Kr(tw - weights[w], n - w) + v, K);
  }
  return K;
}

int K(int tw, int n)
{
  int W = 0;
  for(int i = 0; i <= V; i++)
    W += weights[i];

  vector< vector<int> > K(W+1, vector<int>(V+1));
  for(int j = 0; j <= V; j++) K[0][j] = 0;
  for(int w = 0; w <= W; w++) K[w][0] = 0;

  for(int j = 1; j <= V; j++)
  {
    for(int w = 1; w <= W; w++)
    {
      int wj = weights[j];
      if (wj > w)
      {
        K[w][j] = K[w][j-1];
      }
      else
      {
        K[w][j] = std::max(
          K[w][j-1],
          K[w - wj][j - 1] + values[j]);
      }
    }
  }
  return K[tw][n];
}

int main()
{
  printf("Max K value w repitition is %d\n", Kr(10, 4));
  printf("Max K value w/o repitition is %d\n", K(10, 4));
  return 0;
}
