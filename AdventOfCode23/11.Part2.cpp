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

vector<int> dist;
vector<vector<int>> adjList;
vector<int> visited;
queue<int> q;
vector<string> subsections;
int sz,len;
int new_sz,new_len;
vector<string> grid;
vector<pair<int,int>> navigate={{1,0},{-1,0},{0,1},{0,-1}};


int main() {
  //input
  ifstream fin("input.in");
  stringstream buffer;
  buffer<<fin.rdbuf();
  string line=buffer.str();
  //splitting string into parts
  subsections=strsplit(line, "\n");
  subsections.pop_back();
  sz=subsections.size();
  len=subsections[0].size();
  
  vector<int> need_new_rows;
  vector<int> need_new_cols;
  for (int i=0;i<sz;i++) {
    bool valid=true;
    for (int j=0;j<len;j++) {
      if (subsections[i][j]=='#') {
        valid=false;
        break;
      }
    }
    if (valid) need_new_rows.push_back(i);
  }
  for (int j=0;j<len;j++) {
    bool valid=true;
    for (int i=0;i<sz;i++) {
      if (subsections[i][j]=='#') {
        valid=false;
        break;
      }
    }
    if (valid) need_new_cols.push_back(j);
  }
  
  //int new_sz=sz+need_new_rows.size();
  //int new_len=len+need_new_cols.size();
  
  //vector<string> grid(new_sz,string(new_len,'.'));
  
  vector<pair<long long,long long>> glxy;
  
  for (int i=0;i<sz;i++) {
    for (int j=0;j<len;j++) {
      if (subsections[i][j]=='#') {
        long long y_inc=0;
        for (int c: need_new_cols) {
          if (c<j) y_inc+=999999;
        }
        long long x_inc=0;
        for (int r: need_new_rows) {
          if (r<i) x_inc+=999999;
        }
        //grid[i+x_inc][j+y_inc]='#';
        glxy.push_back({i+x_inc,j+y_inc});
      }
    }
  }
  //for (int i=0;i<new_sz;i++) {
    //for (int j=0;j<new_len;j++) {
      //cout<<grid[i][j];
    //}
    //cout<<endl;
  //}
  long long sum=0;
  int num=glxy.size();
  for (int i=0;i<num;i++) {
    for (int j=i+1;j<num;j++) {
      sum+=abs(glxy[i].first-glxy[j].first)+abs(glxy[i].second-glxy[j].second);
    }
  }
  cout<<sum<<endl;
  return 0;
}