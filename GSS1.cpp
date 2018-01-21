#include "bits/stdc++.h"
using namespace std;
 
const int mod =1e9+7;
const int N =50001;
typedef long long ll;
struct node
{
    int sum,psum,ssum,msum;
};
node segt[5*N];
int a[N];
 
void construct(int index,int start,int endd)
{
    if(start==endd)
    {
        segt[index].sum=a[start];
        segt[index].psum=a[start];
        segt[index].ssum=a[start];
        segt[index].msum=a[start];
        return;
    }
    int mid=(start+endd)/2;
    construct(2*index+1,start,mid);
    construct(2*index+2,mid+1,endd);
 
    segt[index].sum=segt[2*index+1].sum + segt[2*index+2].sum;
    segt[index].psum=max(segt[2*index+1].psum , segt[2*index+1].sum + segt[2*index+2].psum);
    segt[index].ssum=max(segt[2*index+2].ssum , segt[2*index+2].sum + segt[2*index+1].ssum);
    segt[index].msum=max(segt[index].psum,max(segt[index].ssum,max(segt[2*index+1].msum,max(segt[2*index+2].msum,segt[2*index+1].ssum+segt[2*index+2].psum))));
}
node query(int index,int start,int endd,int l,int r)
{
    node result;
    result.sum=result.psum=result.ssum=result.msum=INT_MIN;
    if(l>endd || r < start)
        return result;
    if(l<=start && r>=endd)
        return segt[index];
 
    int mid=(start+endd)/2;
    if(l>mid)
        return query(2*index+2,mid+1,endd,l,r);
    if(r<=mid)
        return query(2*index+1,start,mid,l,r);
    node lt=query(2*index+1,start,mid,l,r);
    node rt=query(2*index+2,mid+1,endd,l,r);
    result.sum=lt.sum+rt.sum;
    result.psum=max(lt.psum,lt.sum+rt.psum);
    result.ssum=max(rt.ssum,rt.sum+lt.ssum);
    result.msum=max(result.psum,max(result.ssum,max(lt.msum,max(rt.msum,lt.ssum+rt.psum))));
    return result;
}
int main()
{
    int n,m,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    construct(0,0,n-1);
    scanf("%d",&m);
    while(m--)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        u--,v--;
        int ans=query(0,0,n-1,u,v).msum;
        printf("%d\n",ans);
    }
    return 0;
}
