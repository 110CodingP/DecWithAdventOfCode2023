#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct Num {
  int val,start,end,row;
  bool operator<(const Num &n) const {
    if (val==n.val) {
        if (row==n.row) {
            if (start==n.start) {
                return end<n.end;
            }
            else {
                return start<n.start;
            }
        }
        else {
            return row<n.row;
        }
    }
    else {
        return val<n.val;
    }
  }
};
struct Star {
  int col,row;
  bool operator<(const Star &s) const { return (row==s.row)?(col<s.col):(row<s.row);}
};
bool is_digit(char ch) {
  if (ch>=48&&ch<=57) return true;
  return false;
}

int power(int a,int b) {
  if (b==0) return 1;
  return a*(power(a,b-1));
}

bool is_adjacent(Num n,Star s) {
    if ((s.row==n.row) &&((s.col+1==n.start)||(s.col==n.end+1))) return true;
    if ((abs(s.row-n.row)==1)&&((s.col>=n.start-1 )&&(s.col<=n.end+1))) return true;
    return false;
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
  myFile.open("gear3.in");
  set<Num> nums;
  set<Star> syms;
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
          Num n;
          n.val=sum;n.start=i;n.end=j-1;n.row=ct;
          nums.insert(n);
          i=--j;
        }
        else if (ch=='*') {
          Star s;
          s.row=ct;
          s.col=i;
          syms.insert(s);
        }
      }
      ct++;
    }
  }
  int gear_ratios=0;
  for (Star s: syms) {
    set<Num> adjacent;
    int increment=1;
    for (Num n: nums) {
        if (is_adjacent(n,s)) {adjacent.insert(n);}
    }
    if (adjacent.size()==2) {
        for (Num n: adjacent) {
            increment *= n.val;
        }
        gear_ratios += increment;
    }
  }
  cout<<gear_ratios<<endl;
  return 0;
}