#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N=205;
const int inf=1e5;
int g[N][N];
 
bool bfs(int s,int t,int par[])
{
    bool mark[t+5];
    for(int i=0;i<t+5;++i)mark[i]=0;
    queue<int>q;
    q.push(s);
    mark[s]=1;
    par[s]=-1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int v=1;v<=t;++v)
        {
            if(!mark[v]&&g[u][v]>0)
            {
                q.push(v);
                par[v]=u;
                mark[v]=1;
            }
        }
    }
    return mark[t]==1;
}
int ford_fulkerson(int s,int t)
{
    int par[N];
    int ans=0;
    while(bfs(s,t,par))
    {
        int path=INT_MAX,u;
        for(int v=t;v!=s;v=par[v])
        {
            u=par[v];
            path=min(path,g[u][v]);
        }
        for(int v=t;v!=s;v=par[v])
        {
            u=par[v];
            g[u][v]-=path;
            g[v][u]+=path;
        }
        ans+=path;
    }
    return ans;
}
 
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i=0;i<=n;++i)for(int j=0;j<=n;++j)g[i][j]=0;
        for(int i=1;i<n;++i)
        {
            int v,u;
            scanf("%d",&v);
            for(int j=1;j<=v;++j)
            {
                scanf("%d",&u);
                if(i==1||u==n)g[i][u]=1;
                else g[i][u]=inf;
            }
        }
        printf("%d\n",ford_fulkerson(1,n));
    }
    return 0;
}
