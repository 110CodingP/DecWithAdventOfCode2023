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
long long sz,len;
vector<string> grid;

map<array<int,4>,int> memo;
void search(int state_i,int state_j,int i,int j) {
  if (i>=sz||i<0||j<0||j>=len) return;
  if (memo.find({state_i,state_j,i,j})!=memo.end()) return;
  memo[{state_i,state_j,i,j}]=1;
  grid[i][j]='#';
  if (subsections[i][j]=='.') search(state_i,state_j,i+state_i,j+state_j);
  if (subsections[i][j]=='\\') search(state_j,state_i,i+state_j,j+state_i);
  if (subsections[i][j]=='/') search(-1*state_j,-1*state_i,i-state_j,j-state_i);
  if (subsections[i][j]=='|'&&(state_i!=0)) search(state_i,state_j,i+state_i,j+state_j);
  if (subsections[i][j]=='-'&&(state_j!=0)) search(state_i,state_j,i+state_i,j+state_j);
  if (subsections[i][j]=='|'&&(state_j!=0)) {
    search(-1*state_j,-1*state_i,i-state_j,j-state_i);
    search(state_j,state_i,i+state_j,j+state_i);
  }
  if (subsections[i][j]=='-'&&(state_i!=0)) {
    search(-1*state_j,-1*state_i,i-state_j,j-state_i);
    search(state_j,state_i,i+state_j,j+state_i);
  }
}

int count() {
  int ret=0;
  for (int i=0;i<sz;i++) {
    for (int j=0;j<len;j++) {
      if (grid[i][j]=='#') ret++;
    }
  }
  return ret;
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
  grid=subsections;
  
  int energized=0;
  for (int i=0;i<len;i++) {
    search(1,0,0,i);
    int ct=count();
    energized=max(energized,ct);
    grid=subsections;
    memo.clear();
    search(-1,0,sz,i);
    ct=count();
    energized=max(energized,ct);
    grid=subsections;
    memo.clear();
  }
  for (int i=0;i<sz;i++) {
    search(0,1,i,0);
    int ct=count();
    energized=max(energized,ct);
    grid=subsections;
    memo.clear();
    search(0,-1,i,len);
    ct=count();
    energized=max(energized,ct);
    grid=subsections;
    memo.clear();
  }
  cout<<energized<<endl;
  return 0; 
}