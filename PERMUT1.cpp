#include "bits/stdc++.h"
using namespace std;
 
const int mod =1e9+7;
const int inf=1e8+7;
const int N =500001;
typedef long long ll;
int dp[13][100];
void solve()
{
    for(int i=0;i<=98;i++)
        dp[0][i]=0;
    for(int i=1;i<=12;i++)
        dp[i][0]=1;
    for(int i=1;i<=12;i++)
    {
        for(int j=1;j<=98;j++)
        {
            int x=j , c=0;
            while(x>=0 && c<i )
            {
                c++;
                dp[i][j]+=dp[i-1][x--];
            }
        }
    }
}
int main()
{
    solve();
    int t;
    cin>>t;
    while(t--)
    {
        int n,k;
        scanf("%d %d",&n,&k);
        printf("%d\n",dp[n][k]);
    }
    return 0;
}
