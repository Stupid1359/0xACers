#include<bits/stdc++.h>
using namespace std;
vector<int>line[400000];
int a[400000],tag[400000],id1[200000],id2[200000],fa[19][400000],siz[400000],dfn[400000],dep[400000],cdfn,psum[400001],vis1[200000],vis2[200000];
void dfs(int t,int f){
	vector<int>::iterator it;
	fa[0][t]=f;
	siz[t]=1;
	dfn[t]=cdfn;
	cdfn++;
	for(it=line[t].begin();it!=line[t].end();it++)
	{
		if(*it==f)continue;
		dep[*it]=dep[t]+1;
		dfs(*it,t);
		siz[t]+=siz[*it];
	}
}
int getnxt(int u,int v){
	int i;
	if(dep[v]<=dep[u])return fa[0][u];
	for(i=18;i>-1;i--)
	{
		if((dep[v]-dep[u]-1)>>i&1)v=fa[i][v];
	}
	if(fa[0][v]==u)return v;
	return fa[0][u];
}
queue<int>q;
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T,n,i,j,u,v,p,t,c;
	vector<int>::iterator it;
	for(cin>>T;T>0;T--)
	{
		cin>>n;
		for(i=0;i<n*2;i++)
		{
			cin>>a[i];
			if(a[i]>0)
			{
				a[i]--;
				tag[i]=0;
				id1[a[i]]=i;
			}
			else
			{
				a[i]=-a[i];
				a[i]--;
				tag[i]=1;
				id2[a[i]]=i;
			}
		}
		for(i=0;i<n*2-1;i++)
		{
			cin>>u>>v;
			line[u-1].push_back(v-1);
			line[v-1].push_back(u-1);
		}
		cdfn=0;
		dep[0]=0;
		dfs(0,-1);
		for(j=1;j<19;j++)
		{
			for(i=0;i<n*2;i++)
			{
				if(fa[j-1][i]==-1)fa[j][i]=-1;
				else fa[j][i]=fa[j-1][fa[j-1][i]];
			}
		}
		for(i=0;i<=n*2;i++)psum[i]=0;
		for(i=0;i<n;i++)
		{
			p=getnxt(id2[i],id1[i]);
			if(p==fa[0][id2[i]])
			{
				psum[dfn[id2[i]]]++;
				psum[dfn[id2[i]]+siz[id2[i]]]--;
			}
			else
			{
				psum[0]++;
				psum[dfn[p]]--;
				psum[dfn[p]+siz[p]]++;
			}
		}
		for(i=1;i<=n*2;i++)psum[i]+=psum[i-1];
		t=-1;
		for(i=0;i<n*2;i++)
		{
			if(psum[dfn[i]]==0)
			{
				t=i;
				break;
			}
		}
		if(t==-1)
		{
			for(i=0;i<n;i++)cout<<'0';
			cout<<'\n';
			for(i=0;i<n*2;i++)line[i].clear();
			continue;
		}
		for(i=0;i<n;i++)
		{
			vis1[i]=0;
			vis2[i]=0;
		}
		q.push(t);
		vis1[a[t]]=1;
		c=0;
		while(!q.empty())
		{
			t=q.front();
			q.pop();
			c++;
			for(it=line[t].begin();it!=line[t].end();it++)
			{
				if(tag[*it]==0)
				{
					if(vis1[a[*it]])continue;
					q.push(*it);
					vis1[a[*it]]=1;
					if(vis2[a[*it]])q.push(id2[a[*it]]);
				}
				else
				{
					if(vis2[a[*it]])continue;
					vis2[a[*it]]=1;
					if(vis1[a[*it]])q.push(*it);
				}
			}
		}
		for(i=0;i<n;i++)
		{
			if(psum[dfn[id1[i]]]==0&&c==n*2)cout<<'1';
			else cout<<'0';
		}
		cout<<'\n';
		for(i=0;i<n*2;i++)line[i].clear();
	}
	return 0;
}
