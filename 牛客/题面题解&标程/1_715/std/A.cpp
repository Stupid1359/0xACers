#include<bits/stdc++.h>
using namespace std;
const int MAXN=125;
const int Mod=1000000007;
const int Inv2=(Mod+1)/2;
int fp(int a,int k)
{
    if(k<0)a=fp(a,Mod-2),k=-k;
    int res=1;
    while(k)
    {
        if(k&1)res=1LL*res*a%Mod;
        a=1LL*a*a%Mod;
        k>>=1;
    }
    return res;
}
int cof[MAXN][MAXN],zero;
bool is_zero(const array<int,4>& c)
{
    for(int i=0;i<4;i++)
        if(c[i])return 0;
    return 1;
}
void mul(const array<int,4>& c,int& n,int& m)
{
    if(is_zero(c))
    {
        zero++;
        return;
    }
    for(int i=n;i>=0;i--)
        for(int j=m;j>=0;j--)
        {
            int tmp=cof[i][j];
            cof[i][j]=1LL*tmp*c[0]%Mod;
            for(int k=1;k<4;k++)
                cof[i+k/2][j+k%2]=(cof[i+k/2][j+k%2]+1LL*tmp*c[k])%Mod;
        }
    n+=(c[2] || c[3]),m+=(c[1] || c[3]);
}
void div(const array<int,4>& c,int& n,int& m)
{
    if(is_zero(c))
    {
        zero--;
        return;
    }
    int t=-1,inv_c=0;
    for(int i=3;i>=0;i--)
        if(c[i])
        {
            t=i,inv_c=fp(c[i],-1);
            break;
        }
    assert(t>=0);
    n-=(c[2] || c[3]),m-=(c[1] || c[3]);
    for(int i=n;i>=0;i--)
        for(int j=m;j>=0;j--)
        {
            int tmp=1LL*cof[i+t/2][j+t%2]*inv_c%Mod;
            for(int k=0;k<3;k++)
                cof[i+k/2][j+k%2]=(cof[i+k/2][j+k%2]-1LL*tmp*c[k]%Mod+Mod)%Mod;
            cof[i+1][j+1]=tmp;
        }
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            cof[i][j]=cof[i+1][j+1],cof[i+1][j+1]=0;
}
int w[MAXN],h[MAXN];
vector<array<int,4>> add[MAXN][MAXN],del[MAXN][MAXN];
int main()
{
    int n,W,H;
    scanf("%d%d%d",&n,&W,&H);
    vector<int> cx{0,W},cy{0,H};
    for(int r=0;r<n;r++)
    {
        scanf("%d%d",&w[r],&h[r]);
        cx.push_back(w[r]);
        cx.push_back(W-w[r]);
        cy.push_back(h[r]);
        cy.push_back(H-h[r]);
    }
    sort(cx.begin(),cx.end());
    cx.erase(unique(cx.begin(),cx.end()),cx.end());
    while(2*cx.back()>=W)cx.pop_back();
    cx.push_back(1LL*W*Inv2%Mod);
    sort(cy.begin(),cy.end());
    cy.erase(unique(cy.begin(),cy.end()),cy.end());
    while(2*cy.back()>=H)cy.pop_back();
    cy.push_back(1LL*H*Inv2%Mod);
    for(int r=0;r<n;r++)
    {
        int inv_w=fp(W-w[r],-1),inv_h=fp(H-h[r],-1);
        for(size_t i=0;i+1<cx.size();i++)
        {
            array<int,4> las;
            for(ssize_t j=cy.size()-2;j>=0;j--)
            {
                int a[2]={0,0},b[2]={0,0};
                if(cx[i]>=w[r])a[0]=(a[0]+w[r])%Mod,a[1]=(a[1]-1+Mod)%Mod;
                if(cx[i]>=W-w[r])a[0]=(a[0]+W-w[r])%Mod;
                else a[1]=(a[1]+1)%Mod;
                if(cy[j]>=h[r])b[0]=(b[0]+h[r])%Mod,b[1]=(b[1]-1+Mod)%Mod;
                if(cy[j]>=H-h[r])b[0]=(b[0]+H-h[r])%Mod;
                else b[1]=(b[1]+1)%Mod;
                array<int,4> c={1,0,0,0};
                for(int x=0;x<2;x++)
                    for(int y=0;y<2;y++)
                        c[x*2+y]=(c[x*2+y]-1LL*a[x]*inv_w%Mod*b[y]%Mod*inv_h%Mod+Mod)%Mod;
                if(j==cy.size()-2)add[i][j].push_back(las=c);
                else if(c!=las)
                {
                    del[i][j].push_back(las);
                    add[i][j].push_back(las=c);
                }
            }
        }
    }
    vector<int> inv(n+2);
    for(int i=1;i<=n+1;i++)
        inv[i]=fp(i,-1);
    vector<vector<int>> pwx(cx.size(),vector<int>(n+2));
    for(size_t i=0;i<cx.size();i++)
    {
        pwx[i][0]=1;
        for(int j=1;j<=n+1;j++)
            pwx[i][j]=1LL*pwx[i][j-1]*cx[i]%Mod;
    }
    vector<vector<int>> pwy(cy.size(),vector<int>(n+2));
    for(size_t i=0;i<cy.size();i++)
    {
        pwy[i][0]=1;
        for(int j=1;j<=n+1;j++)
            pwy[i][j]=1LL*pwy[i][j-1]*cy[i]%Mod;
    }
    int res=0;
    for(size_t i=0;i+1<cx.size();i++)
    {
        cof[0][0]=1,zero=0;
        int degx=0,degy=0;
        for(ssize_t j=cy.size()-2;j>=0;j--)
        {
            for(auto& c : del[i][j])div(c,degx,degy);
            for(auto& c : add[i][j])mul(c,degx,degy);
            if(!zero)for(int x=0;x<=degx;x++)
                for(int y=0;y<=degy;y++)
                {
                    int tmp=1LL*(pwx[i+1][x+1]-pwx[i][x+1]+Mod)*inv[x+1]%Mod;
                    tmp=1LL*tmp*(pwy[j+1][y+1]-pwy[j][y+1]+Mod)%Mod*inv[y+1]%Mod;
                    res=(res+1LL*cof[x][y]*tmp)%Mod;
                }
        }
        for(int x=0;x<=degx;x++)
            for(int y=0;y<=degy;y++)
                cof[x][y]=0;
    }
    res=(1LL*W*H-4LL*res%Mod+Mod)%Mod;
    return 0*printf("%d\n",res);
}
