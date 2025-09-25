#include<bits/stdc++.h>
using namespace std;

int main(){
    int T; scanf("%d",&T);
    while(T--){
        int n,a,b;
        scanf("%d%d%d",&n,&a,&b);
        int r=(n-1)%(a+b);
        int ans=r<a?r+1:0;
        if(ans>=n)puts("Sayonara");
        else printf("%d\n",ans);
    }
    return 0;
}