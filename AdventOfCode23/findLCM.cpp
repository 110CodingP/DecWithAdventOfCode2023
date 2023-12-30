#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
 if (n<2) {return false;}
 for (int i=2;i*i<=n;i++) {
   if (n%i==0) return false;
 }
 return true;
}

int ct(int a,int b) {
  int ret=0;
  while (a%b==0) {
    a/=b;
    ret++;
  }
  return ret;
}

long long findLCM(vector<int> v,int sz) {
  vector<int> prim(1000000);
  for (int i=0;i<sz;i++) {
    if (isPrime(v[i])) {prim[v[i]]=max(prim[v[i]],1);continue;}
     for (int j=2;j*j<=v[i];j++) {
	      if (v[i]%j==0) {
           int q=v[i]/j;
           if (isPrime(j)) {
	     int pr=ct(v[i],j);
	     prim[j]=max(prim[j],pr);
	   }
	   if (isPrime(q)) {
             int pr=ct(v[i],q);
	     prim[q]=max(prim[q],pr);
	   }
	 }
     }
  }
  long long ret=1;
  for (int i=2;i<1000000;i++) {
    for (int j=1;j<=prim[i];j++) {
      ret*=i;
      //cout<<prim[i]<<' '<<i<<endl;
    }
  }
  return ret;
}

int main() {
 int sz;
 cin>>sz;
 vector<int> nums(sz);
 for (int i=0;i<sz;i++)  {
  cin>>nums[i];
  //cout<<isPrime(nums[i]);
 }
 cout<<findLCM(nums,sz);
 return 0;
}
