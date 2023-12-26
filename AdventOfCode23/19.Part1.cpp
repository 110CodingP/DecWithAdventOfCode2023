#include <bits/stdc++.h>
using namespace std;

struct part {
  long x,m,a,s;
  bool operator<(const part &p) const{
    if (x==p.x) {
      if (m==p.m) {
        if (a==p.a) {
          return s<p.s;
        }
        else {
          return a<p.a;
        }
      }
      else {
        return m<p.m;
      }
    }
    else {
      return x<p.x;
    }
  }
};

struct rule {
  char characteristic;
  char comparator;
  string operand;
  string dest;
};

struct workflow{
  vector<rule> rules;
  string last_rule;
};

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
unordered_map<string,workflow> workflows2;

string process(part p,string s) {
  while ((s!="A")&&(s!="R")) {
    bool valid=true;
    if (workflows2[s].rules.empty()) {
      //cout<<workflows2[s].last_rule;
      s=workflows2[s].last_rule;
      continue;
    }
    for (rule r: workflows2[s].rules) {
      int op=(r.characteristic=='x')?p.x:(r.characteristic=='m')?p.m:(r.characteristic=='a')?p.a:p.s;
      //cout<<op<<' ';
      if (r.comparator=='<') {
        if (op < stoi(r.operand)) {
          s=r.dest;
          valid=false;
          break;
        }
      }
      else if (r.comparator=='>') {
        if (op > stoi(r.operand)) {
          s=r.dest;
          valid=false;
          break;
        }
      }
    }
    if (valid) {
      s=workflows2[s].last_rule;
    }
  }
  return s;
}

int main() {
  //input
  ifstream fin("input.in");
  stringstream buffer;
  buffer<<fin.rdbuf();
  string line=buffer.str();
  //splitting string into parts
  vector<string> subsections=strsplit(line, "\n\n");
  vector<string> workflows=strsplit(subsections[0],"\n");
 
  vector<string> parts=strsplit(subsections[1],"\n");
  vector<part> parts2;
  set<part> AC;
  int sz=parts.size();
  int sz2=workflows.size();
  for (int i=0;i<sz2;i++) {
    vector<string> temp=strsplit(workflows[i],"{");
    string name=temp[0];
    string instruction=strsplit(temp[1],"}")[0];
    temp=strsplit(instruction,",");
    workflow wfl;
    wfl.last_rule=temp.back();
    vector<rule> ruleList;
    for (int j=0;j<temp.size()-1;j++) {
      rule r;
      r.characteristic = temp[j][0];
      r.comparator = temp[j][1];
      int len1=temp[j].size();
      vector<string> temp2=strsplit(temp[j],":");
      r.dest=temp2.back();
      int len2=r.dest.size();
      r.operand=temp[j].substr(2,len1-(len2+3));
      ruleList.push_back(r);
    }
    wfl.rules=ruleList;
    workflows2[name]=wfl;
  }
  
  for (int i=0;i<sz;i++) {
    vector<long> num=nums(parts[i]);
    part p{num[0],num[1],num[2],num[3]};
    parts2.push_back(p);
    if (process(p,"in")=="A") AC.insert(p);
  }
  int sum=0;
  for (auto p: AC) {
    sum+=p.x+p.m+p.a+p.s;
  }
  cout<<sum;
  
  return 0; 
}