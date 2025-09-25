#include<bits/stdc++.h>
using namespace std;

const int N=207;
const int B=30;
int a[N][N];
int b[4][5]={{1,1,0,0,0},{0,1,1,0,0},{1,0,1,1,0},{0,0,0,1,1}};
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int L=1,R=0;
    for (int _=0;_<B;++_){
        for (int i=0;i<4;++i){
            for (int j=0;j<5;++j){
                a[L+i][R+j]=b[i][j];
            }
        }
        L+=4, R+=4;
    }
    int n;
    cin>>n;
    for (int i=0;i<30;++i){
        if (n>>i&1) a[0][4*i]=1; 
    }
    cout<<4*B<<"\n";
    for (int i=0;i<4*B;++i){
        for (int j=0;j<4*B;++j){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}