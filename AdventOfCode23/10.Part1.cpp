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

vector<long> dist;
vector<vector<long>> adjList;
vector<bool> visited;
queue<long> q;

void bfs() {
  while (!q.empty()) {
    long u=q.front();
    q.pop();
    for (long i: adjList[u]) {
      if (visited[i]) continue;
      visited[i]=true;
      dist[i]=1+dist[u];
      //cout<<i<<' '<<dist[i]<<endl;
      q.push(i);
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
  int sz=subsections.size();
  int len=subsections[0].size();
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
    if (find(adjList[i].begin(),adjList[i].end(),start)!=adjList[i].end()) adjList[start].push_back(i);
  }
  q.push(start);
  visited[start]=true;
  bfs();
  cout<<*max_element(dist.begin(),dist.end());
  return 0;
}