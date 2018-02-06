#include "bits/stdc++.h"
using namespace std;
 
const int mod =1e9+7 ;
const int N =1000002;
typedef long long ll;
char a[30005];
struct node
{
    int open,close;
};
node segt[5*30005];
void construct(int low,int high,int pos)
{
    if(low==high)
    {
        if(a[low]=='(')
        {
            segt[pos].open=1;
            segt[pos].close=0;
        }
        else
        {
            segt[pos].open=0;
            segt[pos].close=1;
        }
        return;
    }
    int mid=(high+ low)/2;
    construct(low,mid,2*pos+1);
    construct(mid+1,high,2*pos+2);
 
    int bond=min(segt[2*pos+1].open , segt[2*pos+2].close);
    segt[pos].open=segt[2*pos+1].open + segt[2*pos+2].open - bond;
    segt[pos].close=segt[2*pos+1].close + segt[2*pos+2].close - bond;
}
void update(int low,int high,int pos,int l,int r)
{
    if(low > high )return;
    if(l>high||r<low)return;
    if(l<=low&&r>=high)
    {
        if(a[l]=='(')
        {
            segt[pos].open=1;
            segt[pos].close=0;
        }
        else
        {
            segt[pos].open=0;
            segt[pos].close=1;
        }
        return;
    }
    int mid=(low + high)/2;
    update(low,mid,2*pos+1,l,r);
    update(mid+1,high,2*pos+2,l,r);
 
    int bond=min(segt[2*pos+1].open , segt[2*pos+2].close);
    segt[pos].open=segt[2*pos+1].open + segt[2*pos+2].open - bond;
    segt[pos].close=segt[2*pos+1].close + segt[2*pos+2].close - bond;
}
node query(int low,int high,int pos,int l,int r)
{
    node ans;
    if(low == l && high == r)
        return segt[pos];
    int mid=(low + high)/2;
    if(l>mid)
        return query(mid+1,high,2*pos+2,l,r);
    if(r<=mid)
        return query(low,mid,2*pos+1,l,r);
    node lt=query(low,mid,2*pos+1,l,r);
    node rt=query(mid+1,high,2*pos+2,l,r);
 
    int bond=min(lt.open,rt.close);
    ans.open=lt.open + rt.open -bond;
    ans.close=lt.close + rt.close - bond;
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    int n,q;
    for(int i=1;i<=10;i++)
    {
        cin >>n >>a >>q;
        construct(0,n-1,0);
        cout<<"Test "<<i<<":\n";
        while(q--)
        {
            int  val;
            cin>>val;
            if(val)
            {
                if(a[val-1]==')')a[val-1]='(';
                else a[val-1]=')';
                update(0,n-1,0,val-1,val-1);
            }
            else
            {
                node ans=query(0,n-1,0,0,n-1);
                if(ans.open==0 && ans.close==0)
                    cout<<"YES\n";
                else cout<<"NO\n";
            }
        }
    }
    return 0;
}
