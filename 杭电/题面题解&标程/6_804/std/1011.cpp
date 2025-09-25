#include<bits/stdc++.h>
using namespace std;
int cnt[500001],cur[500001];
vector<int>v,vc,ansv;
bool check(int n,int p,int k){
	int i,fc=0;
	for(i=0;i<n;i++)
	{
		if(cur[v[i]%k]==0||cur[v[i]%k]==p)fc++;
		cur[v[i]%k]+=vc[i];
		if(cur[v[i]%k]==0||cur[v[i]%k]==p)fc--;
	}
	for(i=0;i<n;i++)cur[v[i]%k]=0;
	return fc==0;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T,n,m,d,c,i,a,flag;
	for(cin>>T;T>0;T--)
	{
		cin>>n>>m>>c;
		for(i=0;i<=m;i++)cnt[i]=0;
		for(i=0;i<n;i++)
		{
			cin>>a;
			cnt[a]++;
		}
		for(i=0;i<=m;i++)
		{
			if(cnt[i]!=0)
			{
				v.push_back(i);
				vc.push_back(cnt[i]);
			}
		}
		d=v.size();
		if(d<c)
		{
			cout<<"0\n";
			v.clear();
			vc.clear();
			continue;
		}
		if(d==c)
		{
			flag=0;
			for(i=0;i<v.size();i++)
			{
				if(vc[i]!=n/c)flag=1;
			}
			if(flag)cout<<"0\n";
			else cout<<"-1\n";
			v.clear();
			vc.clear();
			continue;
		}
		for(i=c;i<=m/((d-1)/c);i++)
		{
			if(check(d,n/c,i))ansv.push_back(i);
		}
		cout<<ansv.size()<<' ';
		for(i=0;i<ansv.size();i++)
		{
			cout<<ansv[i];
			if(i+1<ansv.size())cout<<' ';
		}
		cout<<'\n';
		ansv.clear();
		v.clear();
		vc.clear();
	}
	return 0;
}
