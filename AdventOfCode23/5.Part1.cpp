#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <sstream>
#include <climits>

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
  ifstream fin("seedvec.in");
  stringstream buffer;
  buffer<<fin.rdbuf();
  string line=buffer.str();
  //splitting string to parts
  vector<string> subsections=strsplit(line, "\n\n");
  
  vector<long> seed= nums(subsections[0]);
  map<long,long> seedMap;
  for (int i=0;i<seed.size();i++) {
    seedMap[seed[i]]=seed[i];
  }
  for (int i=1;i<=7;i++) {
    vector<long> conversion= nums(subsections[i]);
    for (auto i: seedMap) {
      for (int it=0;it<conversion.size();it+=3) {
        if (i.second>=conversion[it+1]&&(i.second<=(conversion[it+1]+conversion[it+2]-1))) {
          seedMap[i.first]=conversion[it]+(i.second-conversion[it+1]);
        }
      }
    }
  }
  int min_loc=INT_MAX;
  for (auto i: seedMap) {
    if (i.second<min_loc) min_loc=i.second;
  }
  cout<<min_loc;
  return 0;
}