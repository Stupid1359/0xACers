#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a), i##ABRACADABRA = (b); i <= i##ABRACADABRA; i++)
#define drep(i, a, b) for (int i = (a), i##ABRACADABRA = (b); i >= i##ABRACADABRA; i--)
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin>>tt;
  while (tt--){
    string s;
    cin>>s;
    if (s[0]==s[2]){
      cout<<"No\n";
      continue;
    }
    if (s[1]=='+'||s[1]=='*'){
      cout<<"Yes\n";
      continue;
    }
    if (s[0]=='0'){
      cout<<"Yes\n";
      continue;
    }
    cout<<"No\n";
  }
  return 0;
}