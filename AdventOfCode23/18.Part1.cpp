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
map<char,int> dig={
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
  {'a',10},
  {'b',11},
  {'c',12},
  {'d',13},
  {'e',14},
  {'f',15},
  };

const int DIM=1000;

vector<string> grid(DIM,string(DIM,'.'));
queue<pair<int,int>> q;
vector<vector<bool>> visited(DIM,vector<bool>(DIM));
vector<pair<int,int>> navigate={{0,1},{0,-1},{1,0},{-1,0}};

void flood() {
  while (!q.empty()) {
    pair<int,int> pt=q.front();
    q.pop();
    grid[pt.first][pt.second]='*';
    for (int i=0;i<4;i++) {
      int new_x=pt.first+navigate[i].first;
      int new_y=pt.second+navigate[i].second;
      if (new_x<0||new_y<0||new_x>=DIM||new_y>=DIM) continue;
      if (visited[new_x][new_y]||grid[new_x][new_y]=='#') continue;
      visited[new_x][new_y]=true;
      q.push({new_x,new_y});
    }
  }
}

int power(int a,int b) {
  if (b==0) return 1;
  return a*power(a,b-1);
}

int hs(string s) {
  int ret=0;
  for (int i=0;i<5;i++) {
    ret+=dig[s[i]]*power(16,4-i);
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
  vector<string> subsections=strsplit(line, "\n");
  int sz=subsections.size();
  //cout<<sz<<endl;
  int len=subsections[0].size();
  
  long prev_i=DIM/2;
  long prev_j=DIM/2;
  long curr_i=DIM/2;
  long curr_j=DIM/2;
  
  grid[curr_i][curr_j]='#';
  long area=0;
  long num_ext=1;
  for (int i=0;i<sz;i++) {
    vector<string> word=strsplit(subsections[i]," ");
    string num=word[2].substr(2,5);
    //cout<<num<<endl;
    int reps=hs(num);
    char dir=word[2][7];
    //cout<<dir<<" "<<reps<<endl;
    for (int ct=0; ct<reps;ct++) {
      if (dir=='0') {
        curr_j++;
      }
      if (dir=='2') {
        curr_j--;
      }
      if (dir=='1') {
        curr_i++;
      }
      if (dir=='3') {
        curr_i--;
      }
      area+= curr_i*prev_j-curr_j*prev_i;
      prev_i=curr_i;
      prev_j=curr_j;
      num_ext++;
    }
  }
  area/=2;
  cout<<area+num_ext/2+1<<endl;
  return 0; 
}