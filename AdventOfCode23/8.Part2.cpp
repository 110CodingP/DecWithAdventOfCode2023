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
  vector<string> has_A_end;
  for (auto s: graph) {
    if ((s.first)[2]=='A') has_A_end.push_back(s.first);
  }
  //map<string,string> curr_node;
  //for (string s: has_A_end) {
    //curr_node[s]=s;
  //}
  //Brute force takes a lot of time so find the LCM!
  //for(int ct=1;;ct++) {
    //bool valid=true;
    //for (string s: has_A_end) {
      //for (char c: instructions) {
        //if (c=='R') curr_node[s]=graph[curr_node[s]].second;
        //else curr_node[s]=graph[curr_node[s]].first;
      //}
      //if (curr_node[s][2]!='Z') {
        //valid=false;
        //break;
      //}
    //}
    //if (valid) {
      //cout<<ct*sz<<endl;
      //break;
    //}
  //}
  int sz_A_end=has_A_end.size();
  vector<long long> steps(sz_A_end);
  for (int i=0;i<sz_A_end;i++) {
    string curr_node=has_A_end[i];
    for (int ct=1;;ct++) {
      for (char c: instructions) {
        if (c=='R') curr_node=graph[curr_node].second;
        else curr_node=graph[curr_node].first;
      }
      if (curr_node[2]=='Z') {
        steps[i]=ct;
        break;
      }
    }
  }
  long long max_val=*max_element(steps.begin(),steps.end());
  for (int i=1;;i++) {
    long long prod=i*max_val;
    bool is_LCM=true;
    for (long long step: steps) {
      if (prod%step!=0) {is_LCM=false;break;}
    }
    if (is_LCM) {cout<<prod*sz<<endl;break;}
  }
  
  return 0;
}