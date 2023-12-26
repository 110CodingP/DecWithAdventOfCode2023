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
vector<vector<pair<string,int>>> boxes(256);

long long hs(string s) {
  int ret=0;
  for (char c: s) {
    if (c!='\n') {
      ret+=(int) c;
      ret*=17;
      ret%=256;
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
  subsections=strsplit(line, ",");
  sz=subsections.size();
  //cout<<sz<<endl;
  for (int i=0;i<sz;i++) {
    string request=subsections[i];
    int pos=0;
    for (int j=0;j<subsections[i].size();j++) {
      if (subsections[i][j]=='='||subsections[i][j]=='-') {pos=j;break;}
    }
    string label=request.substr(0,pos);
    int box_num=hs(label);
    if (request[pos]=='=') {
      int focus=request[pos+1]-48;
      bool isThere=false;
      for (auto &pr: boxes[box_num]) {
        if (pr.first==label) {
          isThere=true;
          pr.second=focus;
        }
      }
      if (!isThere) {
        boxes[box_num].push_back({label,focus});
      }
    }
    else {
      int len=boxes[box_num].size();
      for (int k=0;k<len;k++) {
        if (boxes[box_num][k].first==label) {
          boxes[box_num].erase(boxes[box_num].begin()+k);
        }
      }
    }
  }
  long long sum=0;
  for (int i=0;i<255;i++) {
    int len=boxes[i].size();
    for (int j=0;j<len;j++) {
      //cout<<(i+1)<<' '<<(j+1)<<' '<<boxes[i][j].second<<endl;
      sum+=(i+1)*(j+1)*(boxes[i][j].second);
      //cout<<boxes[i][j].first<<' '<<boxes[i][j].second<<' ';
    }
    //cout<<endl;
  }
  cout<<sum<<endl;
  return 0; 
}