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


long ways(int pos,string s,vector<long> v) {
  if (pos==s.size()) {
    //cout<<s<<endl;
    vector<long> consec;
    int ct=0;
    for (int i=0;i<s.size();i++) {
      if (s[i]=='#') ct++;
      else if (ct>0) {
        consec.push_back(ct);
        ct=0;
      }
    }
    if (ct>0) consec.push_back(ct);
    if (v==consec) return 1;
    return 0;
  }
  if (s[pos]!='?') return ways(pos+1,s,v);
  long count=0;
  s[pos]='#';
  count+=ways(pos+1,s,v);
  s[pos]='.';
  count+=ways(pos+1,s,v);
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
  long sum=0;
  
  for (int i=0;i<sz;i++) {
    vector<string> vec=strsplit(subsections[i]," ");
    string s=vec[0];
    vector<long> num=nums(vec[1]);
    sum+=ways(0,s,num);
  }
  cout<<sum<<endl;
  return 0; 
}