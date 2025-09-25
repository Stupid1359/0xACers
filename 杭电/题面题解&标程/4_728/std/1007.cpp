#include <bits/stdc++.h>
#define ll int
using namespace std;

set<ll> sl,sr;
set<ll> s0,s3;
set<ll> s4;
ll n,q,a[500005],b[500005];
ll tree[2000005],tree2[500005];

inline void upd(ll pos,ll v){
	while (pos<=n){
		tree2[pos]+=v;
		pos+=pos&-pos;
	}
}

inline ll query(ll pos){
	ll ans=0;
	while (pos){
		ans+=tree2[pos];
		pos-=pos&-pos;
	}
	return ans;
}

void upd(ll root,ll l,ll r,ll pos,ll v) {
	if (l==r) {
		tree[root]=v;
		return;
	}
	ll mid=(l+r)>>1;
	if (pos<=mid)upd(root<<1,l,mid,pos,v);
	else upd(root<<1|1,mid+1,r,pos,v);
	tree[root]=max(tree[root<<1],tree[root<<1|1]);
}

ll querymx(ll root,ll l,ll r,ll L,ll R) {
	if (L>R||L<0||R>n)return 0;
	if (L<=l&&r<=R) {
		return tree[root];
	}
	ll mid=(l+r)>>1,ans=0;
	if (L<=mid)ans=max(ans,querymx(root<<1,l,mid,L,R));
	if (R>mid)ans=max(ans,querymx(root<<1|1,mid+1,r,L,R));
	return ans;
}

inline void ins(ll l,ll r) {
	if (r-l+1<=4){
		return;
	} 
	sl.insert(l);
	sr.insert(r);
	upd(1,1,n,r,r-l+1);
}

inline bool check(ll l,ll r) {
	if (l<0||r>n)return 0;
	if (r-l+1==4) {
		bool fl=0;
		fl|=(a[l]==1&&a[l+1]==2&&a[l+2]==1&&a[l+3]==0);
		fl|=(a[l]==2&&a[l+1]==0&&a[l+2]==2&&a[l+3]==0);
		return fl;
	}
	if (r-l+1==5) {
//		cout<<l<<","<<r<<":"<<(a[l]==2&&a[l+1]==1&&a[l+2]==2&&a[l+3]==0&&a[l+4]==0)<<"\n";
		return (a[l]==2&&a[l+1]==1&&a[l+2]==2&&a[l+3]==0&&a[l+4]==0);
	}
	if (r-l+1<=6) {
		return 0;
	}
	bool fl=1;
	ll N=r-l+1;
	fl&=(a[l]==N-4);
	fl&=(a[l+1]==2);
	fl&=(a[l+2]==1);
	fl&=(a[r]==0);
	fl&=(a[r-1]==0);
	fl&=(a[r-2]==0);
	fl&=(a[r-3]==1);
//	cout<< l<<","<<r<<":"<<a[l]<<" "<<a[l+1]<<" "<< a[l+2]<<" "<<a[r-3]<<" "<<a[r-2]<<" "<<a[r-1]<<" "<<a[r]<<"\n";
	if (!fl)return 0;
	ll rl=l+3,rr=r-4;
//	cerr<<"#"<<rl<<","<<rr<<":"<< n<<"\n"; 
	if (rl<=rr&&query(rr)-query(rl-1)!=rr-rl+1)return 0;
	return fl;
}

void UPD(ll l,ll r) {
	if (a[l]==r)return;
	if(sl.size()) {
		auto wl=sl.upper_bound(l);
		if (wl!=sl.begin()) {
			ll tl=*prev(wl),tr=*sr.lower_bound(tl);
			if (tl<=l&&l<=tr) {
				sl.erase(tl);
				sr.erase(tr);
				upd(1,1,n,tr,0);
			}
		}
	}
	for (ll j=l;j<=l+3;j++){
		if (check(j-3,j)){
			s4.erase(j-3);
		}
	}
	if (a[l]==0) {
		s0.erase(l);
		upd(l,-1);
	} else if (a[l]!=1&&a[l]!=2) {
		s3.erase(l);
	}
	a[l]=r;
	if (a[l]==0) {
		s0.insert(l);
		upd(l,1);
	} else if (a[l]!=1&&a[l]!=2) {
		s3.insert(l);
	}
	for (ll j=l; j<=l+4; j++) {
		if (j<=l+3) {
			if (check(j-3,j)) {
				s4.insert(j-3);
			}
		}
		if (check(j-4,j)) {
			ins(j-4,j);
		}
	}
	// as n-4
	if (r>=3) {
		if (check(l,l+r+3)) {
			ins(l,l+r+3);
		}
	}
	// as 2
	if (l>=2&&r==2&&a[l-1]>=3) {
		if (check(l-1,l+a[l-1]+2)) {
			ins(l-1,l+a[l-1]+2);
		}
	}
	// as 1
	if (l>=3&&r==1&&a[l-1]==2&&a[l-2]>=3) {
		if (check(l-2,l+a[l-2]+1)) {
			ins(l-2,l+a[l-2]+1);
		}
	}
	// as 0...001000
	if(l>3&&(r==0||r==1)) {
		if (s3.size()) {
			auto ps=s3.upper_bound(l);
			if (ps!=s3.begin()) {
				ps=prev(ps);
				ll pl=*ps;
				if (check(pl,pl+a[pl]+3)) {
					ins(pl,pl+a[pl]+3);
				}
			}
		}
	}
}

inline ll read(){
	ll x=0;char c=getchar();
	while (!isdigit(c))c=getchar();
	while (isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
} 

int main() {
//	freopen("test1.in","r",stdin);
//	freopen("test1.out","w",stdout);
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	ll T;
	T=read();
	while (T--) {
		n=read();q=read();
		for (ll i=1; i<=n; i++) {
			b[i]=read();
			s0.insert(i);
			upd(i,1); 
		}
		for (ll i=1; i<=n; i++) {
			UPD(i,b[i]);
		}
		for (ll i=1; i<=q; i++) {
			ll op,l,r;
			op=read();l=read();r=read();
			if (op==1) {
				UPD(l,r);
			} else {
				ll z=0;
				auto ps=s4.lower_bound(l);
				if (ps!=s4.end()&&(*ps)>=l&&(*ps)+3<=r){
					z=4;
				}
				auto wl=sl.lower_bound(l);
				
				if (wl==sl.end()) {
					cout<<z<<"\n";
				} else {
					ll wr=*sr.lower_bound(*wl);
					cout<< max(z,querymx(1,1,n,wr,r)) <<"\n";
				}
			}
		}
		s0.clear();
		s3.clear();
		sl.clear();
		sr.clear();
		s4.clear();
		for (ll i=1; i<=4*n; i++)tree[i]=0;
		for (ll i=1; i<=n; i++)a[i]=b[i]=tree2[i]=0;
	}

	return 0;
}
