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
int sz,len;

map<array<int,3>,long long> memo;

long long ways(int pos,string s,vector<long> v,int curr_len,int num_pos) {
  if (memo.find({pos,curr_len,num_pos})!=memo.end()) return memo[{pos,curr_len,num_pos}]; 
  if (pos==s.size()) {
    //cout<<s<<endl;
    if (num_pos==v.size()&&curr_len==0) return 1;
    if (num_pos==v.size()-1&&(v[num_pos]==curr_len)) return 1;
    return 0;
  }
  long long count=0;
  for (char c: {'.','#'}) {
    if (s[pos]==c||s[pos]=='?') {
      if (c=='.'&&curr_len==0) {
        count+=ways(pos+1,s,v,0,num_pos);
      }
      else if ((c=='.')&&(curr_len>0)&&(num_pos<v.size())&&(v[num_pos]==curr_len)) {
        count+=ways(pos+1,s,v,0,num_pos+1);
      }
      else if (c=='#') {
        count+=ways(pos+1,s,v,curr_len+1,num_pos);
      }
    }
  }

  memo[{pos,curr_len,num_pos}]=count;
  return count;
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
  long long sum=0;
  
  for (int i=0;i<sz;i++) {
    vector<string> vec=strsplit(subsections[i]," ");
    string s=vec[0];
    string temp="";
    for (int ct=0;ct<4;ct++) {
      temp+='?';
      for (char c: s) {
        temp+=c;
      }
    }
    s+=temp;
    vector<long> num=nums(vec[1]);
    int num_sz=num.size();
    for (int c=0;c<4;c++) {
      for (int j=0;j<num_sz;j++) {
        num.push_back(num[j]);
      }
    }
    //for (auto j: num) cout<<j<<' ';
    //cout<<endl;
    sum+=ways(0,s,num,0,0);
    memo.clear();
  }
  cout<<sum<<endl;
  return 0; 
}