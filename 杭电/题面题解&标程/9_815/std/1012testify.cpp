#include<bits/stdc++.h>
using namespace std;
int T,n,m,cnt[100005];
bool cmp(int x,int y){
	if(cnt[x]==cnt[y])return x<y;
	return cnt[x]>cnt[y];
}
vector<int> ord,re;
int main(){
	for(scanf("%d",&T);T;T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			int x;scanf("%d",&x);
			if(cnt[x]==0)ord.emplace_back(x);
			cnt[x]++;
		}
		re=ord;
		sort(re.begin(),re.end(),cmp);
		int res=0;
		for(int i=0;i<ord.size();i++)
			res+=(ord[i]!=re[i]);
		printf("%d\n",res);
		
		for(int i:ord)
			cnt[i]=0;
		
		ord.clear(); re.clear();
	}
	return 0;
}
