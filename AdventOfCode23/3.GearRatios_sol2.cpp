#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <map>
#include <set>
using namespace std;

bool is_digit(char ch) {
  if (ch>=48&&ch<=57) return true;
  return false;
}

int power(int a,int b) {
  if (b==0) return 1;
  return a*(power(a,b-1));
}

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

int main() {
  freopen("gear.out","w",stdout);
  ifstream myFile;
  myFile.open("gear2.in");
  set<array<int,4>> nums;
  set<pair<char,array<int,2>>> syms;
  string myLine;
  int ct=0;
  if (myFile.is_open()) {
    while (myFile) {
      getline(myFile,myLine);
      for (int i=0;i<myLine.size();i++) {
        char ch=myLine[i];
        if (ch=='.') continue;
        if (is_digit(ch)) {
          vector<int> num;
          int j;
          for (j=i;j<myLine.size();j++) {
            ch=myLine[j];
            if (!is_digit(ch)) break;
            num.push_back(dig[ch]);
          }
          int sum=0;
          for (int k=0;k<num.size();k++) {
            sum+=num[k]*power(10,num.size()-1-k);
          }
          nums.insert({sum,i,j-1,ct});
          i=--j;
        }
        else {
          syms.insert({ch,{i,ct}});
        }
      }
      ct++;
    }
  }
  set<array<int,4>> part_nums;
  for (auto s: syms) {
    for (auto n: nums) {
      if ((s.second[1]==n[3])&&((s.second[0]+1==n[1])||(s.second[0]==n[2]+1))) {
        // cout<<s.second[1]<<' '<<n[3]<<' '<<s.second[0]<<' '<<n[1]<<' '<<n[2]<<' '<<n[0]<<endl;
        part_nums.insert(n);
      }
      else if ((abs(s.second[1]-n[3])==1)&&((s.second[0]>=n[1]-1 )&&(s.second[0]<=n[2]+1))) {
        part_nums.insert(n);
      }
    }
  }
  int sum_final=0;
  for (auto p: part_nums) {
    sum_final+=p[0];
  }
  cout<<sum_final;
  return 0;
}