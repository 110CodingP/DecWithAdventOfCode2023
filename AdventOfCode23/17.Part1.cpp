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

vector<vector<int>> grid;
long long sz,len;
priority_queue<pair<long,array<int,4>>> pq;
set<array<int,4>> visited;
long modDijkstra() {
  while (!pq.empty()) {
    long heat_loss=-pq.top().first;
    array<int,4> u=pq.top().second;
    pq.pop();
    if (visited.count(u)>0) continue;
    visited.insert(u);
    if(u[0]==sz-1&&u[1]==len-1) {return heat_loss;}
    if (u[2]==0) {
      long sum=heat_loss;
      for (int i=1;i<=3;i++) {
        int i_dw=u[0]+i;
        if (i_dw>=sz) break;
        sum+=grid[i_dw][u[1]];
        pq.push({-sum,{i_dw,u[1],1,0}});
      }
      sum=heat_loss;
      for (int i=1;i<=3;i++) {
        int i_dw=u[0]-i;
        if (i_dw<0) break;
        sum+=grid[i_dw][u[1]];
        pq.push({-sum,{i_dw,u[1],-1,0}});
      }
    }
    
    if (u[3]==0) {
      int sum=heat_loss;
      for (int i=1;i<=3;i++) {
        int j_dw=u[1]+i;
        if (j_dw>=len) break;
        sum+=grid[u[0]][j_dw];
        pq.push({-sum,{u[0],j_dw,0,1}});
      }
      sum=heat_loss;
      for (int i=1;i<=3;i++) {
        int j_dw=u[1]-i;
        if (j_dw<0) break;
        sum+=grid[u[0]][j_dw];
        pq.push({-sum,{u[0],j_dw,0,-1}});
      }
    }
  }
}

int main() {
  //input
  ifstream fin("input.in");
  stringstream buffer;
  buffer<<fin.rdbuf();
  string line=buffer.str();
  //splitting string into parts
  vector<string> subsections=strsplit(line, "\n");
  sz=subsections.size();
  //cout<<sz<<endl;
  len=subsections[0].size();
  grid.resize(sz,vector<int>(len));
  for (int i=0;i<sz;i++) {
   for (int j=0;j<len;j++) {
      grid[i][j]=subsections[i][j]-48;
      //cout<<grid[i][j];
    }
    //cout<<endl;
  }
  pq.push({-grid[0][0],{0,0,0,1}});
  pq.push({-grid[0][0],{0,0,1,0}});
 
  long long min_len=modDijkstra()-grid[0][0];
  cout<<min_len<<endl;
  
  return 0; 
}