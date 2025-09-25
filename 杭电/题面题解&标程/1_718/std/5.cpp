#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int head[N], tot, dis[N], cnt, num;
int s, t, vis[N], T;
int n, m;
map<int, int> mp, mp2;
struct node{
	int next, to, w;
}edge[N<<2];
struct dp{
	int w, id;
	inline bool operator <(const dp &x) const{
		return w > x.w;
	}
};
vector<int> p[N];
void add(int u, int v, int w){
	tot++;
	edge[tot].next = head[u];
	edge[tot].to = v;
	edge[tot].w = w;
	head[u] = tot;
}
void dijkstra(){
	queue<dp> q;
	q.push({0, s});
	memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
	dis[s] = 0;
	while(q.size()){
		int u = q.front().id;
		q.pop();
		vis[u] = 1;
		for(int i = head[u]; i; i = edge[i].next){
			int v = edge[i].to;
			if(dis[v] > dis[u] + edge[i].w){
				dis[v] = dis[u] + edge[i].w;
				if(!vis[v])q.push({dis[v], v});
			}
		}
	}
}
void check(){
	cin >> n >> m;
	long long u, v, w;
	mp.clear(), mp2.clear();
	tot = num = cnt = 0;
	memset(head, 0, sizeof(head));
    for(int i = 1; i <= n; i++) p[i].clear();
	for(int i = 1; i <= m; i++){
		cin >> u >> v >> w;
		if(!mp[w]) mp[w] = ++cnt;
		if(!mp2[u + mp[w]*n]) mp2[u + mp[w]*n] = ++num;
		if(!mp2[v + mp[w]*n]) mp2[v + mp[w]*n] = ++num;
		add(mp2[u + mp[w]*n], mp2[v + mp[w]*n], 0), add(mp2[v + mp[w]*n], mp2[u + mp[w]*n], 0);
		p[u].push_back(mp2[u + mp[w]*n]), p[v].push_back(mp2[v + mp[w]*n]);
	}
	s = 0, t = ++num;
	for(int i = 1; i <= n; i++){
		num++;
		for(auto v: p[i]){
			add(v, num, 0), add(num, v, 1);
			if(i == 1) add(s, v, 1);
			if(i == n) add(v, t, 0);
		}
	}
	dijkstra();
	cout << dis[t] << '\n';
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while(T--) check();
}