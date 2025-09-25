#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N=100009,B=400;
int n,m,q,a[N],b[N],c[N],f;
int val[B+5][2*B+5],top[B+5],pre[B+5];
int sum[B+5][B+5],tg[B+5];
void rebuild(){
	for(int i=1,t=0;i<=f;i++)for(int j=1;j<=top[i];j++)b[++t]=val[i][j];
	for(int i=1;i<=f;i++)top[i]=tg[i]=0;
	if(m<=B)for(int i=1;i<=f;i++)memset(sum[i],0,sizeof(sum[i]));
	for(int i=1,bl=1;i<=n;i++){
		val[bl][++top[bl]]=b[i];
		if(m<=B)sum[bl][i%m]+=b[i];
		if(i%B==0)bl++;
	}
	for(int i=1;i<=f;i++)pre[i]=pre[i-1]+top[i];
}
void del(int x){
	for(int i=1;i<=f;i++)if(val[i][top[i]]>=x){
		for(int j=1;j<=top[i];j++)if(val[i][j]==x){
			for(int k=j;k<top[i];k++)val[i][k]=val[i][k+1];
			top[i]--;
			break;
		}
		if(m>B)break;
		tg[i]=0;
		memset(sum[i],0,sizeof(sum[i]));
		for(int j=1;j<=top[i];j++)sum[i][(pre[i-1]+j)%m]+=val[i][j];
		for(int j=i+1;j<=f;j++){
			tg[j]++;
			if(tg[j]>=m)tg[j]-=m;
		}
		break;
	}
	for(int i=1;i<=f;i++)pre[i]=pre[i-1]+top[i];
}
void add(int x){
	for(int i=1;i<=f;i++)if(val[i][top[i]]>=x||i==f){
		for(int j=top[i];~j;j--)if(val[i][j]>x)val[i][j+1]=val[i][j];else{val[i][j+1]=x;break;}
		top[i]++;
		if(m>B)break;
		tg[i]=0;
		memset(sum[i],0,sizeof(sum[i]));
		for(int j=1;j<=top[i];j++)sum[i][(pre[i-1]+j)%m]+=val[i][j];
		for(int j=i+1;j<=f;j++){
			tg[j]--;
			if(tg[j]<0)tg[j]+=m;
		}
		break;
	}
	for(int i=1;i<=f;i++)pre[i]=pre[i-1]+top[i];
}
int qry(int x){
	int res=0;
	if(m<=B)for(int i=1;i<=f;i++)if(pre[i]<=x)res+=sum[i][(x+tg[i])%m];
	else if(pre[i-1]<x){
		int y=x;
		while(y>pre[i-1]){
			res+=val[i][y-pre[i-1]];
			y-=m;
		}
	}else break;
	else{
		int y=x,p=1;
		while(pre[p]<x)p++;
		while(y>0){
			while(pre[p-1]>=y)p--;
			res+=val[p][y-pre[p-1]];
			y-=m;
		}
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	sort(b+1,b+1+n);
	for(int i=1,bl=1;i<=n;i++){
		f=bl;
		val[bl][++top[bl]]=b[i];
		if(m<=B)sum[bl][i%m]+=b[i];
		if(i%B==0)bl++;
	}
	for(int i=1;i<=f;i++)pre[i]=pre[i-1]+top[i];
	int lans=0;
	for(int tc=1;tc<=q;tc++){
		int x,y,z;cin>>x>>y>>z;
		x=(x+lans)%n+1;
		y=(y+lans)%(int)(1e9)+1;
		z=(z+lans)%n+1;
//		cout<<x<<' '<<y<<' '<<z<<endl;
		del(a[x]);
		add(a[x]=y);
		cout<<(lans=qry(z))<<endl;
		if(tc%B==0)rebuild();
	}
	return 0;
}