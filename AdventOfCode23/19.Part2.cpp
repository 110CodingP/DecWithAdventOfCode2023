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

const int DIM=4000;

unordered_map<string,workflow> workflows2;

unsigned long long sum=0;


void process(string s,array<unsigned long long,8> xmas) {
  //cout<<sum<<endl;
  if (s=="A") {
    //for (auto i: xmas)  cout<<i<<' ';
    //cout<<endl;
    sum+=(xmas[1]-xmas[0]+1)*(xmas[3]-xmas[2]+1)*(xmas[5]-xmas[4]+1)*(xmas[7]-xmas[6]+1);
    return;
  }
  if (s=="R") {
    //for (auto i: xmas)  cout<<i<<' ';  
    return;
  }
  for (rule r: workflows2[s].rules) {
    //cout<<r.comparator;
    if (r.comparator=='<') {
      pair<int,unsigned long long> oldval;
      //cout<<r.characteristic;
      switch(r.characteristic) {
        case 'x': oldval={1,xmas[1]};xmas[1]=min(stoull(r.operand)-1,xmas[1]);break;
        case 'm': oldval={3,xmas[3]};xmas[3]=min(stoull(r.operand)-1,xmas[3]);break;
        case 'a': oldval={5,xmas[5]};xmas[5]=min(stoull(r.operand)-1,xmas[5]);break;
        case 's': oldval={7,xmas[7]};xmas[7]=min(stoull(r.operand)-1,xmas[7]);break;
      }
      //cout<<oldval.first<<' '<<oldval.second<<' '<<r.operand<<endl;
      if (!((stoull(r.operand)-1)<xmas[oldval.first-1])) {
        process(r.dest,xmas);
      }
      if (!(stoull(r.operand)>oldval.second)) {
        xmas[oldval.first]=oldval.second;
        xmas[oldval.first-1]=max(stoull(r.operand),xmas[oldval.first-1]);
        //for (auto i: xmas)  cout<<i<<' ';
        continue;
      }
      else {
        xmas[oldval.first]=oldval.second;
        //cout<<"hi";
        break;
      }
    }
    if (r.comparator=='>') {
      pair<int,unsigned long long> oldval;
      switch(r.characteristic) {
        case 'x': oldval={0,xmas[0]};xmas[0]=max(stoull(r.operand)+1,xmas[0]);break;
        case 'm': oldval={2,xmas[2]};xmas[2]=max(stoull(r.operand)+1,xmas[2]);break;
        case 'a': oldval={4,xmas[4]};xmas[4]=max(stoull(r.operand)+1,xmas[4]);break;
        case 's': oldval={6,xmas[6]};xmas[6]=max(stoull(r.operand)+1,xmas[6]);break;
      }
      if (!((stoull(r.operand)+1)>xmas[oldval.first+1])) {
        process(r.dest,xmas);
      }
      if (!(stoull(r.operand)<oldval.second)) {
        xmas[oldval.first]=oldval.second;
        xmas[oldval.first+1]=min(stoull(r.operand),xmas[oldval.first+1]);
        continue;
      }
      else {
        xmas[oldval.first]=oldval.second;
        break;
      }
    }
  }
  //for (auto i: xmas)  cout<<i<<' ';
  //cout<<workflows2[s].last_rule;
  process(workflows2[s].last_rule,xmas);
  
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
  array<unsigned long long,8> xmas={1,DIM,1,DIM,1,DIM,1,DIM};
  process("in",xmas);
  cout<<sum<<endl;
  
  return 0; 
}