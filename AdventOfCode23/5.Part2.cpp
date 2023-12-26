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
  ifstream fin("seedvec.in");
  stringstream buffer;
  buffer<<fin.rdbuf();
  string line=buffer.str();
  //splitting string to parts
  vector<string> subsections=strsplit(line, "\n\n");
  
  vector<long> seedRange= nums(subsections[0]);
  vector<pair<long,long>> seed;
  for (int i=0;i<seedRange.size();i+=2) {
    seed.push_back({seedRange[i],seedRange[i+1]});
  }
  map<pair<long,long>,long> seedMap;
  for (int i=0;i<seed.size();i++) {
    seedMap[seed[i]]=seed[i].first;
  }
  //for (auto i: seedMap) {
    //cout<<i.first.first<<' '<<i.first.second<<' '<<i.second<<' ';
  //}
  //cout<<endl;
  
  for (int i=1;i<=7;i++) {
    vector<long> conversion= nums(subsections[i]);
    set<pair<pair<long,long>,long>> to_add_later;
    for (int j=0;j<conversion.size();j+=3) {
    set<pair<pair<long,long>,long>> to_add_now;
    set<pair<pair<long,long>,long>> to_erase;
      for (auto it: seedMap) {
        if (it.second>=conversion[j+1]&&(it.second+it.first.second)<=(conversion[j+1]+conversion[j+2])) {
          to_add_later.insert({{it.first.first,it.first.second},conversion[j]+it.second-conversion[j+1]});
          to_erase.insert(it);
        }
        else if ((it.second>=conversion[j+1])&&(it.second<=(conversion[j+1]+conversion[j+2]))) {
          to_add_later.insert({{it.first.first,conversion[j+1]+conversion[j+2]-it.second},conversion[j]+it.second-conversion[j+1]});
          to_add_now.insert({{it.first.first-it.second+conversion[j+1]+conversion[j+2],it.first.second-(conversion[j+1]+conversion[j+2]-it.second)},it.second+(conversion[j+1]+conversion[j+2]-it.second)});
          to_erase.insert(it);
        }
        else if (((it.second+it.first.second)<=(conversion[j+1]+conversion[j+2]))&&(it.second+it.first.second>=conversion[j+1])) {
          to_add_later.insert({{conversion[j+1]-it.second+it.first.first,it.first.second-(conversion[j+1]-it.second)},conversion[j]});
          to_add_now.insert({{it.first.first,conversion[j+1]-it.second},it.second});
          to_erase.insert(it);
        }
      }
      for (auto sub: to_erase) {seedMap.erase(sub.first);}
      for (auto add: to_add_now) {seedMap[add.first]=add.second;}
      }
      for (auto add: to_add_later) {seedMap[add.first]=add.second;}
      //for (auto i: seedMap) {
        //cout<<i.first.first<<' '<<i.first.second<<' '<<i.second<<' ';
       //cout<<endl;
      //}
  }
  int min_loc=INT_MAX;
  for (auto i: seedMap) {
    //cout<<i.first.first<<' '<<i.second<<endl;
    //ct++;
    if (i.second<min_loc&&(i.first.second!=0)) min_loc=i.second;
  }
  cout<<min_loc<<endl;
  return 0;
}