#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

map<char,int> dig{
  {'0',0},
  {'1',1},
  {'2',2},
  {'3',3},
  {'4',4},
  {'5',5},
  {'6',6},
  {'7',7},
  {'8',8},
  {'9',9},
};
bool is_digit(char ch) {
  if (ch>=48&&ch<=57) return true;
  return false;
}
int power(int a,int b) {
  if (b==0) return 1;
  return a*power(a,b-1);
}
int main() {
  freopen("scratch.out","w",stdout);
  ifstream myFile;
  myFile.open("input.in");
  string myLine;
  int pts=0;
  if (myFile.is_open()) {
    while (myFile) {
      getline(myFile,myLine);
      set<int> win_nums;
      set<int> money_nums;
      int i=0;
      int sz=myLine.size();
      int ct=0;
      for (i=0;i<sz;i++) {
        char ch= myLine[i];
        if (ch=='|') {break;}
        if (is_digit(ch)) {
          vector<int> num;
          int j;
          for (j=i;j<sz;j++) {
            ch=myLine[j];
            if (!is_digit(ch)) break;
            num.push_back(dig[ch]);
          }
          int sum=0;
          int num_sz=num.size();
          for (int k=0;k<num_sz;k++) {
            sum+=num[k]*power(10,num.size()-1-k);
          }
          if (ct==0) {ct++;} 
          else {win_nums.insert(sum);
            //cout<<sum<<endl;
          }
          i=--j;
        }
      }
      for (int s=i;s<sz;s++) {
        char ch=myLine[s];
        if (is_digit(ch)) {
          vector<int> num;
          int j;
          for (j=s;j<sz;j++) {
            ch=myLine[j];
            if (!is_digit(ch)) break;
            num.push_back(dig[ch]);
          }
          int sum=0;
          int num_sz=num.size();
          for (int k=0;k<num_sz;k++) {
            sum+=num[k]*power(10,num.size()-1-k);
          }
          if (!win_nums.empty()) {
            if (win_nums.count(sum)!=0) {
              //cout<<sum<<' '<<win_nums.count(sum)<<endl;
              money_nums.insert(sum);
            }
            s=--j;
          }
        }
      }
      int increment=0;
      if (!money_nums.empty()) {
        int money_sz=money_nums.size();
        increment=power(2,money_sz-1);
      }
      pts+=increment;
    }
  }
  cout<<pts;
  return 0;
}

