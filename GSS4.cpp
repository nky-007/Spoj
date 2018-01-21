#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,i,l,r,q;
ll segt[500000],a[100000];
 
void constructsegtree(int low,int high,int pos)
{
    if(low==high)
    {
        segt[pos]=a[low];
        return;
    }
    int mid=(low+high)/2;
    constructsegtree(low,mid,2*pos+1);
    constructsegtree(mid+1,high,2*pos+2);
    segt[pos]=(segt[2*pos+1]+segt[2*pos+2]);
}
void updaterange(int l,int r,int low,int high,int pos)
{
    if(low>high)return;
    if(l>high||r<low)return;
    if(l<=low&&r>=high)
    {
        if(segt[pos]==(high-low+1))
           return;
        else if(low==high){segt[pos]=sqrt(segt[pos]);return;}
    }
    int mid=(low+high)/2;
    updaterange(l,r,low,mid,2*pos+1);
    updaterange(l,r,mid+1,high,2*pos+2);
    segt[pos]=(segt[2*pos+1]+segt[2*pos+2]);
}
ll updatequery(int l,int r,int low,int high,int pos)
{
    if(low>high)return 0;
    if(l>high||r<low)return 0;
    if(l<=low&&r>=high)
        return segt[pos];
    int mid=(low+high)/2;
    return (updatequery(l,r,low,mid,2*pos+1)+(updatequery(l,r,mid+1,high,2*pos+2)));// change only this???
}
int main()
{
    int c=0;
    while(scanf("%d",&n)!=EOF){
            c++;
    for(i=0;i<n;i++)scanf("%lld",&a[i]);
    constructsegtree(0,n-1,0);
    scanf("%d",&q);
    printf("Case #%d:\n",c);
    while(q--)
    {
        int type;
        scanf("%d",&type);
        if(type==0)
        {
            scanf("%d %d",&l,&r);
            if(l>r)swap(l,r);
            l--,r--;
            updaterange(l,r,0,n-1,0);
        }
        else
        {
            scanf("%d %d",&l,&r);
            if(l>r)swap(l,r);
            l--,r--;
            ll ans=updatequery(l,r,0,n-1,0);
            printf("%lld\n",ans);
        }
    }
    printf("\n");
    }
    return 0;
}
