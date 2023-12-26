#include <bits/stdc++.h>
using namespace std;


vector<long> nums(string s){
    vector<long> toReturn;
    long num = 0;
    bool counting = false;
    bool negative = false;

    for(int i = 0; i < s.size(); i++){
        if(s[i] <= '9' && s[i] >= '0'){
            counting = true;
            num *= 10;
            num += (s[i] - '0');
        }else if(s[i] == '-'){
            negative = true;
        }else if(counting){
            if(negative){
                toReturn.push_back(num*(-1));
            }else{
                toReturn.push_back(num);
            }
            num = 0;
            counting = false;
            negative = false;
        }else if(negative){
            negative = false;
        }
    }
    if(counting){
        if(negative){
            toReturn.push_back(num*(-1));
        }else{
            toReturn.push_back(num);
        }
        num = 0;
    }
    return toReturn;
}


vector<string> strsplit(string str, string delim){
    int prevInd = 0;
    vector<string> toReturn;
    for(int i = 0; i < str.size(); i++){
        if(str.substr(i, delim.length()) == delim){
            toReturn.push_back(str.substr(prevInd, i-prevInd));
            prevInd = i + delim.length();
            i = prevInd - 1;
        }
    }
    toReturn.push_back(str.substr(prevInd));
    return toReturn;
}
vector<string> grid;

long long count_cols() {
  long long ct=0;
  long long sz=grid.size();
  long long len=grid[0].size(); 
  for (int i=0;i<len-1;i++) {
    int bad=0;
    int rem=(len-i-1>i+1)?i+1:len-(i+1);
    for (int j=0;j<rem;j++) {
      for (int r=0;r<sz;r++) {
        if (grid[r][i-j]!=grid[r][i+j+1]) {
          bad++;
          if (bad>1) break;
        }
      }
      if (bad>1) break;
    }
    if (bad==1) {
      ct+=(i+1);
      //cout<<i+1;
    }
  }
  return ct;
}


int main() {
  //input
  ifstream fin("input.in");
  stringstream buffer;
  buffer<<fin.rdbuf();
  string line=buffer.str();
  //splitting string into parts
  vector<string> subsections=strsplit(line, "\n\n");
  long long n=subsections.size();
  long long rows=0;
  long long cols=0;
  
  for (int i=0;i<n;i++) {
    grid=strsplit(subsections[i],"\n");
    cols+=count_cols();
    long long sz=grid.size();
    long long len=grid[0].size();
    vector<string> grid_tr(len,string(sz,'A'));
    for (int r=0;r<len;r++) {
      for (int c=0;c<sz;c++) {
        grid_tr[r][c]=grid[c][r];
      }
    }
    grid=grid_tr;
    rows+=count_cols();
  }
  cout<<rows*100+cols<<endl;
  return 0; 
}