#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<cstdio>
#include<cctype>
#include<vector>
#include<bitset>
#include<random>
#include<ctime>
#include<queue>
#include<cmath>
#include<list>
#include<map>
#include<set>
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define pll pair<long long,long long>
#define FF fflush(stdout)
#define inf 0x3f3f3f3f
#define endl "\n"
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
//char buf[1<<20],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int s=0,f=1;
    char x=getchar();
    while(!isdigit(x))f=(x=='-'?-1:1),x=getchar();
    while(isdigit(x))s=s*10+x-'0',x=getchar();
    return s*f;
}
const int p=998244353;
//ll ksm(int a,int b){ll ans=1,bs=a;while(b){if(b&1)ans=ans*bs%p;bs=bs*bs%p;b>>=1;}return ans;}
mt19937 rd(time(0));
#define reaD read
int s[100005],ss[100005];
void remove_zero(vector<int> &v)
{
    while(!v.empty() && v.back() == 0) v.pop_back();
}
bool le(vector<int> a,vector<int> b)
{
    remove_zero(a);
    remove_zero(b);
    if(a.size()<b.size()) return true;
    if(a.size()>b.size()) return false;
    int n=a.size();
    for(int i=n-1;i>=0;i--)
    if(a[i]!=b[i])
    return a[i]<b[i];
    return false;
}
vector<int> my_minus(vector<int> a,vector<int> b,int m)
{
    if(le(a,b))swap(a,b);
    assert(a.size()==b.size());
    int n=a.size();
    vector<int> c(n);
    bool flag=false;
    for(int i=0;i<n;i++)
    {
        c[i]=a[i]-b[i]-flag;
        if(c[i]<0)flag=true,c[i]+=m;
        else flag=false;
    }
    assert(!flag);
    remove_zero(c);
    return c;
}
int cal(vector<int> a,int m)
{
    remove_zero(a);
    if(a.empty())return 0;
    ll ans=0;
    ll v=1;
    for(int i=0;i<a.size();i++)
    {
        ans=(ans+a[i]*v)%p;
        v=v*m%p;
    }
    return ans;
}
int main()
{
    int T=read();
    while(T--)
    {
        int n=read(),m=read();
        for(int i=1;i<=n;i++)
        {
            s[i]=read();
        }
        sort(s+1,s+n+1);
        vector<int> ans(n,1e9);
        if(n%2==1&&s[1]==0)
        {
            if(s[2]==1)
            {
                swap(s[1],s[2]);
                vector<int> a,b;
                for(int i=n/2+1;i>=1;i--)
                a.pb(s[i]);
                for(int i=n/2+2;i<=n;i++)
                b.pb(s[i]);
                b.pb(0);
                ans=my_minus(a,b,m);
                swap(s[1],s[2]);
            }
            for(int i=1;i<n;i++)
            s[i]=s[i+1];
            n--;
        }
        if(n%2==0)
        {
            int tot=0;
            int cnt0=0;
            for(int i=1;i<=n;i++)
            {
                if(i<n&&s[i]==s[i+1])
                {
                    i++;
                    cnt0+=(s[i]==0);
                }
                else
                {
                    ss[++tot]=s[i];
                }
            }
            n=tot;
            if(n==0)
            {
                puts("0");
                continue;
            }
            for(int i=1;i<=n;i++)
            s[i]=ss[i];
            assert(n%2==0);
            int mi=1e9;
            vector<int> pos;
            for(int i=1;i<n;i++)
            {
                int v=s[i+1]-s[i];
                if(v<mi)mi=v,pos.clear(),pos.pb(i);
                else if(v==mi)pos.pb(i);
            }
            assert(mi);
            int p1=0,p2=0;
            for(int i=0;i<pos.size();i++)
            {
                if(pos[i]<=n/2)
                p1=pos[i];
                else
                {
                    p2=pos[i];
                    break;
                }
            }
            auto solve=[&](int pos) -> vector<int> {
                vector<int> a,b;
                a.pb(s[pos+1]);
                b.pb(s[pos]);
                int len=n/2-1;
                int now=1;
                while(len)
                {
                    if(now==pos||now==pos+1)
                    {
                        now++;
                        continue;
                    }
                    a.pb(s[now]);
                    len--;
                    now++;
                }
                len=n/2-1;
                now=n;
                while(len)
                {
                    if(now==pos||now==pos+1)
                    {
                        now--;
                        continue;
                    }
                    b.pb(s[now]);
                    len--;
                    now--;
                }
                // cout<<a.size()<<" "<<b.size()<<endl;
                reverse(a.begin(), a.end());
                reverse(b.begin(), b.end());
                return my_minus(a,b,m);
            };
            if(p1)
            {
                vector<int> tmp=solve(p1);
                if(le(tmp,ans))ans=tmp;
            }
            if(p2)
            {
                vector<int> tmp=solve(p2);
                if(le(tmp,ans))ans=tmp;
            }
            printf("%d\n",cal(ans,m));
        }
        else
        {
            vector<int> a,b;
            for(int i=n/2+1;i>=1;i--)
            a.pb(s[i]);
            for(int i=n/2+2;i<=n;i++)
            b.pb(s[i]);
            b.pb(0);
            printf("%d\n",cal(my_minus(a,b,m),m));
        }
    }
    return 0;
}