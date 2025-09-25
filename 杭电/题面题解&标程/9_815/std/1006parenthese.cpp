#include<bits/stdc++.h>
using namespace std;
#define ll int
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define fe(i,e) for(int i=0;i<e.size();i++)
#define vi vector<ll>
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d rd()
#define pb push_back
ll n,res;
char c[100010];
bool vis[100010];
bool ch(ll l,ll r){
	f(i,l,r-1)if(c[i]=='('&&c[i+1]==')')return 1;
	return 0;
}
int main(){
	scanf("%s",c+1);n=strlen(c+1);
	assert(1<=n&&n<=10000);
	f(i,1,n)assert(c[i]=='('||c[i]==')'||('a'<=c[i]&&c[i]<='z'));
	f(i,1,n-1)if(c[i]=='('&&c[i+1]==')')vis[i]=1;
	f(i,1,n){
		bool ok=0;ll x=1;
		while(i-x>=1&&i+x<=n){
			if(c[i-x]!=c[i+x])break;
			ok|=vis[i-x]|vis[i+x-1];
			res+=ok;
			x++;
		}
	}f(i,1,n-1)if(c[i]==c[i+1]){
		bool ok=0;ll x=1;
		while(i-x>=1&&i+1+x<=n){
			if(c[i-x]!=c[i+1+x])break;
			ok|=vis[i-x]|vis[i+x];
			res+=ok;
			x++;
		}
	}
	cout<<res<<endl;
	return 0;
}
