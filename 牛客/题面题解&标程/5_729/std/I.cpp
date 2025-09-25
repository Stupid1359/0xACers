#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n;
    if(n&1){
        cout<<2*(n+n/2+1);
    }else{
        cout<<2*(n+1+n/2);
    }
    return 0;
}