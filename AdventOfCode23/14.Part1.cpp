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

int main() {
  //input
  ifstream fin("input.in");
  stringstream buffer;
  buffer<<fin.rdbuf();
  string line=buffer.str();
  //splitting string into parts
  vector<string> subsections=strsplit(line, "\n");
  long long sz=subsections.size();
  //cout<<sz<<endl;
  long long len=subsections[0].size();
  long load=0;
  
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
    int sz1=pos.size();
    for (int i=0;i<sz1;i++) {
      if (pos[i]==(sz-1)) break;
      for (int j=1;j<=num[i];j++) {
        load+=sz-(pos[i]+j);
      }
    }
    //for (int i=0;i<sz1;i++) cout<<pos[i]<<' ';
    //cout<<endl;
    //for (int i=0;i<num.size();i++) cout<<num[i]<<' ';
    //cout<<endl;
  }
  cout<<load<<endl;
  return 0; 
}