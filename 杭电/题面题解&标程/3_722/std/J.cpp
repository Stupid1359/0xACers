#include<bits/stdc++.h>
using namespace std;
void Solve(){
    int x,y; cin>>x>>y;
    if((x+y)&1){
        cout<<"-1\n";
        return;
    } int A=1; while(1){
        if(x==y){
            cout<<A<<'\n';
            return;
        } if(x>y)swap(x,y);
        y-=x; x<<=1; ++A;
        if(A>64){
            cout<<"-1\n";
            return;
        }
    }
}
signed main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int Ks; cin>>Ks;
    while(Ks--)Solve();
}