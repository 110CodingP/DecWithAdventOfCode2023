#include <bits/stdc++.h>
using namespace std;


vector<long long> nums(string s){
    vector<long long> toReturn;
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

long long power(long long a, long long b) {
  if (b==0) return 1;
  return a*power(a,b-1);
}

int main() {
  //input
  ifstream fin("6.Part1.in");
  stringstream buffer;
  buffer<<fin.rdbuf();
  string line=buffer.str();
  //splitting string to parts
  vector<string> subsections=strsplit(line, "\n");
  vector<long long> Time=nums(subsections[0]);
  vector<long long> Record=nums(subsections[1]);
  
  int sz=Time.size();
  int prod=1;
  
  for (int i=0;i<sz;i++) {
    int ways=0;
    for (long t=1;t<Time[i];t++) {
      if (t*(Time[i]-t)>=Record[i]) ways++;
    }
    prod*=ways;
  }
  
  cout<<prod<<endl;
  return 0;
}