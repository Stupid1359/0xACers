#include <bits/stdc++.h>
#define ld long double
using namespace std;
const ld eps=1e-12;
const ld inf=1e9;
int n,m,X,Y;
ld a[15],b[15];
ld h[15],w[15];
inline ld f(ld x)
{
	static ld ret;ret=0.0L;
	for(int i=m;i>=0;i--) ret=ret*x+b[i];
	return ret;
}
inline ld fd(ld x)
{
	static ld ret;ret=0.0L;
	for(int i=m-1;i>=0;i--) ret=ret*x+a[i];
	return sqrtl(ret*ret+1);
}
inline ld calc(ld l,ld r)
{
	ld mid=(l+r)/2;
	return (r-l)*(fd(l)+4*fd(mid)+fd(r))/6;
}
ld solve(ld l,ld r,ld eps,ld val,int dep)
{
	ld mid=(l+r)/2;
	ld fl=calc(l,mid),fr=calc(mid,r);
	if(fabsl(fl+fr-val)<=15*eps && dep<=0) return fl+fr+(fl+fr-val)/15;
	return solve(l,mid,eps/2,fl,dep-1)+solve(mid,r,eps/2,fr,dep-1);
}
ld calculus(ld l,ld r){return solve(l,r,eps,calc(l,r),7);}
ld pos[10020][15];
ld dis[10020][15];
ld dp[10020][15];
ld lmt,ans;
ld calc(ld x,ld h1,ld h2)
{
	ld y=f(x)+h1;
	ld l=x,r=lmt,xx,yy;
	ld k=(y-Y)/(x-X),b=-k*x+y;
	while(r-l>eps)
	{
		xx=(l+r)/2;
		yy=f(xx);
		if(sqrtl((x-xx)*(x-xx)+(y-h1-yy)*(y-h1-yy))<max(h1,h2) || yy<k*xx+b) l=xx;
		else r=xx;
	}
	return xx;
}
void output(ld x){static char s[25];sprintf(s,"%.4Le",x);for(int i:{0,1,2,3,4,5,6,7})printf("%c",s[i]);printf("%c",s[strlen(s)-1]);}
int o[15];
void solve()
{
	scanf("%d%d%d%d",&n,&m,&X,&Y);
	lmt=2*powl(inf,1.0L/m);
	for(int i=0;i<m;i++) scanf("%Lf",&a[i]),b[i+1]=a[i],a[i]*=i+1;
	for(int i=0;i<n;i++) scanf("%Lf%Lf",&h[i],&w[i]);
	ans=inf;
	for(int i=0;i<n;i++) o[i]=i;
	do
	{
		ld pos=0.0,res=0.0,tot=0.0;
		for(int i=1;i<n;i++)
		{
			ld nxt=calc(pos,h[o[i-1]],h[o[i]]);
			res=res+calculus(pos,nxt);
			tot+=res*w[o[i]];
			pos=nxt;
		}
		ans=min(ans,tot);
	}
	while(next_permutation(o,o+n));
	output(ans);
	printf("\n");
}
int main()
{
	int t;
	cin>>t;
	while(t--) solve();
}

/*

我们发现给定的山坡函数在 $\mathbb{R}_{\ge 0}$ 上是一个下凸函数，同时太阳在第二象限且纵坐标大于所有大楼。于是，大楼底部的横坐标与影子最远处的横坐标呈正相关。

这样一来，我们枚举这些大楼之间的相对顺序，那么最优的建造方案一定是第一座大楼建在原点，接下来的每一座大楼都尽可能靠近原点。可以通过二分等方法求出每一座大楼需要建造在什么位置。

最后需要做的事就是计算从原点走到给定坐标需要的距离。这其实是在计算一段曲线的长度。设曲线的方程是 $y=f(x)$，那么曲线在 $x \in [l,r]$ 的范围内长度就是 $\int_l^r \sqrt{f'(x)^2+1}\ \text{d}x$。这个函数不容易直接求原函数，但可以使用辛普森积分的方式近似地求出数值。

*/
