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

void bfs() {
  while (!q.empty()) {
    int u=q.front();
    q.pop();
    for (int i: adjList[u]) {
      if (visited[i]) continue;
      visited[i]=true;
      dist[i]=1+dist[u];
      q.push(i);
    }
  }
}

void flood(int x,int y) {
  if (x<0||y<0||x>=new_sz||y>=new_len) return;
  if (grid[x][y]!='.') return;
  grid[x][y]='X';
  for (int i=0;i<4;i++) {
    int x2=x+navigate[i].first;
    int y2=y+navigate[i].second;
    flood(x2,y2);
  }
  
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
  len=subsections[0].size();
  adjList.resize(sz*len);
  visited.resize(sz*len);
  dist.resize(sz*len);
  long start=0;
  for (int i=0;i<sz;i++) {
    string s=subsections[i];
    for (int j=0;j<len;j++) {
      if (s[j]=='|') {adjList[i*len+j].push_back((i-1)*len + j);adjList[i*len+j].push_back((i+1)*len +j);}
      else if (s[j]=='-') {adjList[i*len+j].push_back(i*len +j-1); adjList[i*len+j].push_back(i*len +j+1);}
      else if (s[j]=='L') {adjList[i*len+j].push_back((i-1)*len +j); adjList[i*len+j].push_back(i*len +j+1);}
      else if (s[j]=='J') {adjList[i*len+j].push_back((i-1)*len +j); adjList[i*len+j].push_back(i*len +j-1);}
      else if (s[j]=='7') {adjList[i*len+j].push_back((i+1)*len+j); adjList[i*len+j].push_back(i*len +j-1);}
      else if (s[j]=='F') {adjList[i*len+j].push_back((i+1)*len+j); adjList[i*len+j].push_back(i*len +j+1);}
      else if (s[j]=='S') {start=i*len+j;}
    }
  }
  for (int i=0;i<sz*len;i++) {
    if (find(adjList[i].begin(),adjList[i].end(),start)!=adjList[i].end()) {
      adjList[start].push_back(i);
    }
  }
  int start_y=start/len;
  int start_x=start%len;
  int y1=adjList[start][0]/len;
  int y2=adjList[start][1]/len;
  int x1=adjList[start][0]%len;
  int x2=adjList[start][1]%len;
  
  if (abs(start_y-y1)==1&&abs(start_y-y2)==1) subsections[start_y][start_x]='|';
  if (abs(start_x-x1)==1&&abs(start_x-x2)==1) subsections[start_y][start_x]='-';
  if (((x1==start_x)&&(start_y-y1==1)&&(x2==start_x+1)&&(y2==start_y))||((x2==start_x)&&(start_y-y2)==1&&(x1==start_x+1)&&(y1==start_y))) subsections[start_y][start_x]='L';
  if (((x1==start_x)&&(start_y-y1==1)&&(x2+1==start_x)&&(y2==start_y))||((x2==start_x)&&(start_y-y2==1)&&(x1+1==start_x)&&(y1==start_y))) subsections[start_y][start_x]='J';
  if (((x1==start_x)&&(start_y-y1==-1)&&(x2+1==start_x)&&(y2==start_y))||((x2==start_x)&&(start_y-y2==-1)&&(x1+1==start_x)&&(y1==start_y)))subsections[start_y][start_x]='7';
  if (((x1==start_x)&&(start_y-y1==-1)&&(x2==start_x+1)&&(y2==start_y))|((x2==start_x)&&(start_y-y2==-1)&&(x1==start_x+1)&&(y1==start_y))) subsections[start_y][start_x]='F';

  q.push(start);
  visited[start]=true;
  bfs();
  for (int i=0;i<sz;i++) {
    for (int j=0;j<len;j++) {
      if (!visited[i*len+j]) subsections[i][j]='.';
    }
  }
  
  
  //expansion
  new_sz=sz*3;
  new_len=len*3;
  grid.resize(new_sz,string(new_len,'.'));
  for (int i=0;i<sz;i++) {
    for (int j=0;j<len;j++) {
      if (subsections[i][j]=='|') {
        grid[i*3][j*3+1]='|';
        grid[i*3+1][j*3+1]='|';
        grid[i*3+2][j*3+1]='|';
      }
      if (subsections[i][j]=='-') {
        grid[i*3+1][j*3]='-';
        grid[i*3+1][j*3+1]='-';
        grid[i*3+1][j*3+2]='-';
      }
      if (subsections[i][j]=='L') {
        grid[i*3][j*3+1]='|';
        grid[i*3+1][j*3+1]='L';
        grid[i*3+1][j*3+2]='-';
      }
      if (subsections[i][j]=='J') {
        grid[i*3][j*3+1]='|';
        grid[i*3+1][j*3+1]='J';
        grid[i*3+1][j*3]='-';
      }
      if (subsections[i][j]=='7') {
        grid[i*3+1][j*3]='-';
        grid[i*3+1][j*3+1]='7';
        grid[i*3+2][j*3+1]='|';
      }
      if (subsections[i][j]=='F') {
        grid[i*3+1][j*3+2]='-';
        grid[i*3+1][j*3+1]='F';
        grid[i*3+2][j*3+1]='|';
      }
    }
  }
  
  flood(0,0);
  int ct=0;
  vector<pair<int,int>> sqr={{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};
  for (int i=0;i<sz;i++) {
    for (int j=0;j<len;j++) {
      bool val=true;
      for (auto sq: sqr) {
        if (grid[i*3+sq.first][j*3+sq.second]!='.') {
          val=false;
          break;
        }
      }
      if (val) ct++;
    }
  }
  cout<<ct<<endl;
  return 0;
}