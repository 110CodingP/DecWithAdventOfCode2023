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
  vector<string> subsections=strsplit(line, "\n\n");
  
  string instructions= subsections[0];
  vector<string> nodeInfo=strsplit(subsections[1],"\n");
  map<string,pair<string,string>> graph;
  for (auto s: nodeInfo) {
    string node=s.substr(0,3);
    string left=s.substr(7,3);
    string right=s.substr(12,3);
    graph[node]={left,right};
  }
  //for (auto s: graph) {
    //cout<<s.first<<' '<<s.second.first<<' '<<s.second.second<<' '<<endl;
  //}
  int sz=instructions.size();
  string curr_node="AAA";
  for(int ct=1;;ct++) {
    for (char c: instructions) {
      if (c=='R') curr_node=graph[curr_node].second;
      else curr_node=graph[curr_node].first;
    }
    if (curr_node=="ZZZ") {
      cout<<ct*sz<<endl;
      break;
    }
  }
  return 0;
}