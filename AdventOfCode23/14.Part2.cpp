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

vector<string> subsections;
long long sz;
long long len;
map<string,long long> grids;

void tilt() {
  for (int col=0;col<len;col++) {
      vector<int> pos;
      vector<int> num;
      pos.push_back(-1);
      int ct=0;
      for (int row=0;row<sz;row++) {
        if (subsections[row][col]=='#') {
          num.push_back(ct);
          pos.push_back(row);
          ct=0;
        }
        if (subsections[row][col]=='O') {
          ct++;
        }
      }
      if (subsections[sz-1][col]!='#') {
        num.push_back(ct);
      }
      //for (int i: num) cout<<num[i]<<' ';
      //cout<<endl;
      int sz1=pos.size();
      for (int r=0;r<sz;r++) {
        if (subsections[r][col]!='#') {
          subsections[r][col]='.';
        }
      }
      for (int i=0;i<sz1;i++) {
        if (pos[i]==(sz-1)) break;
        for (int j=1;j<=num[i];j++) {
          subsections[(pos[i]+j)][col]='O';
        }
      }
      //cout<<sz<<' '<<len<<endl;
    }
}

void roll() {
  for (int rt=0;rt<4;rt++) {
    tilt();
    long long new_sz=subsections.size();
    long long new_len=subsections[0].size();
    vector<string> grid(new_len,string(new_sz,'.'));
    for (int i=0;i<new_len;i++) {
      for (int j=0;j<new_sz;j++) {
        grid[i][j]=subsections[new_sz-j-1][i];
      }
    }
    subsections=grid;
    sz=new_len;
    len=new_sz;
  }
}

int run=1;
long long find_cycle() {
  roll();
  string s;
  for (int i=0;i<sz;i++) {
    for (int j=0;j<len;j++) {
      s+=subsections[i][j];
    }
  }
  if (grids.find(s)!=grids.end()) return grids[s];
  grids[s]=run;
  run++;
  return find_cycle();
}

int main() {
  //input
  ifstream fin("input.in");
  stringstream buffer;
  buffer<<fin.rdbuf();
  string line=buffer.str();
  //splitting string into parts
  subsections=strsplit(line, "\n");
  sz=subsections.size();
  //cout<<sz<<endl;
  len=subsections[0].size();
  long load=0;
  int extra=find_cycle();
  int cyc=run-extra;
  int rem=(1000000000-(run))%cyc;
  for (int i=0;i<rem;i++) {
    roll();
  }
  for (int col=0;col<len;col++) {
    for (int row=0;row<sz;row++) {
      if (subsections[row][col]=='O') load+=sz-(row);
    }
  }
  cout<<load;
  
  
  return 0; 
}