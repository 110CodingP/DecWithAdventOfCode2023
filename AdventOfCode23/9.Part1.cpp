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

long extrapolate(vector<long> v) {
  if (*max_element(v.begin(),v.end())==*min_element(v.begin(),v.end())&&*min_element(v.begin(),v.end())==0) return 0;
  int sz=v.size();
  vector<long> diff;
  for (int i=0;i<sz-1;i++) {
    diff.push_back(v[i+1]-v[i]);
  }
  return v[sz-1]+extrapolate(diff);
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
  long sum=0;
  for (int i=0;i<sz;i++) {
    vector<long> num=nums(subsections[i]);
    sum+=extrapolate(num);
  }
  cout<<sum;
  return 0;
}