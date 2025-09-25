#include<iostream>
#include<algorithm>
using namespace std;
const int days[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
int Case,n,m,i,l,r,k,year,month,day,g[555],ans;
inline bool check(int year,int month,int day){
  if(month==2&&day==29&&year%4)return 0;
  if(month<3){
    year-=1;
    month+=12;
  }
  int c=year/100,y=year-100*c;
  int w=c/4-2*c+y+y/4+(26*(month+1)/10)+day-1;
  w=(w%7+7)%7;
  return w>=1&&w<=5;
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>k>>l>>r;
    n=0;
    for(month=1;month<=12;month++)for(day=1;day<=days[month];day++){
      m=0;
      for(year=l;year<=r;year++)m+=check(year,month,day);
      g[++n]=m;
    }
    sort(g+1,g+n+1);
    ans=0;
    for(i=1;i<=k;i++)ans+=g[i];
    cout<<ans<<"\n";
  }
}