#include <bits/stdc++.h>
using namespace std;

struct cjn {
  vector<string> onodes;
  vector<string> inodes;
  vector<bool> state;
};

struct flipflop {
  vector<string> nodes;
  bool state;
};

struct broadcaster {
  vector<string> nodes;
};

struct sgn {
  string from;
  string to;
  bool strength;
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

long long btn=0;
broadcaster brdcstr;
map<string, flipflop> ff;
map<string, cjn> cn;
queue<sgn> toBeProcessed;
bool done=false;
long long first=0,second=0,third=0,fourth=0;

void press() {
  btn++;
  while (!toBeProcessed.empty()) {
    //cout<<pr.first<<' '<<pr.second<<"*\n";
    sgn u=toBeProcessed.front();
    toBeProcessed.pop();
    string name=u.to;
    string from=u.from;
    bool sig=u.strength;
    if (!sig) {
      if (name=="xj") {first=(first>0)?first:btn;}
      if (name=="qs") {second=(second>0)?second:btn;}
      if (name=="kz") {third=(third>0)?third:btn;}
      if (name=="km") {fourth=(fourth>0)?fourth:btn;}
    }
    if (name=="brdcstr") {
      for (auto node: brdcstr.nodes) {
        //cout<<name<<endl;
        //cout<<node<<' ';
        toBeProcessed.push({"brdcstr",node,0});
      }
      //cout<<endl;
    }
    if (ff.find(name)!=ff.end()) {
      //cout<<name<<endl;
      if (!sig) {
        ff[name].state=!ff[name].state;
        for (auto node : ff[name].nodes) {
          if (ff[name].state) {
            toBeProcessed.push({name,node,1});
          }
          else {
            toBeProcessed.push({name,node,0});
          }
        }
      }
    }
    if (cn.find(name)!=cn.end()) {
      //cout<<cn[name].inodes.size()<<endl;
      bool allhigh=true;
      for (int i=0;i<cn[name].inodes.size();i++) {
        if (cn[name].inodes[i]==from) {
          cn[name].state[i]=sig;
        }
        //cout<<cn[name].state[i]<<"$"<<endl;
        if (!cn[name].state[i]) {
          //cout<<cn[name].inodes[i]<<endl;
          allhigh=false;
        }
      }
      bool sig_emit=!allhigh;
      for (auto node: cn[name].onodes) {
        toBeProcessed.push({name,node,sig_emit});
      }
    }
  }
  return;
}

int main() {
  //input
  ifstream fin("input.in");
  stringstream buffer;
  buffer<<fin.rdbuf();
  string line=buffer.str();
  //cout<<line;
  //splitting string into parts
  vector<string> subsections=strsplit(line, "\n");
  int sz=subsections.size();
  //cout<<sz<<endl;
  for (int i=0;i<sz;i++) {
    vector<string> temp=strsplit(subsections[i]," -> ");
    if (temp[0][0]=='b') {
      vector<string> node=strsplit(temp[1],", ");
      for (int j=0;j<(int) node.size();j++) {
        //cout<<node[j];
        brdcstr.nodes.push_back(node[j]);
      }
    }
    if (temp[0][0]=='%') {
      flipflop fp;
      string name=temp[0].substr(1,temp[0].size()-1);
      vector<string> node=strsplit(temp[1],", ");
      for (int j=0;j<(int) node.size();j++) {
        fp.nodes.push_back(node[j]);
      }
      fp.state=0;
      ff[name]=fp;
    }
    if (temp[0][0]=='&') {
      cjn cj;
      string name=temp[0].substr(1,temp[0].size()-1);
      vector<string> node=strsplit(temp[1],", ");
      for (int j=0;j<(int) node.size();j++) {
        cj.onodes.push_back(node[j]);
      }
      cn[name]=cj;
    }
  }
  
  for (auto &c: cn) {
    if (find(brdcstr.nodes.begin(),brdcstr.nodes.end(),c.first)!=brdcstr.nodes.end()) {
      c.second.inodes.push_back("brdcstr");
      c.second.state.push_back(0);
    }
    for (auto f: ff) {
      if (find(f.second.nodes.begin(),f.second.nodes.end(),c.first)!=f.second.nodes.end()) {
        c.second.inodes.push_back(f.first);
        c.second.state.push_back(0);
      }
    }
    for (auto c2: cn) {
      if (find(c2.second.onodes.begin(),c2.second.onodes.end(),c.first)!=c2.second.onodes.end()) {
        c.second.inodes.push_back(c2.first);
        c.second.state.push_back(0);
      }
    }
  }
  //for (auto c: cn) {
    //cout<<c.first<<endl;
    //cout<<c.second.inodes.size()<<endl;
  //}
  sgn s{"btn","brdcstr",0};
  toBeProcessed.push(s);
  
  for (int i=0;;i++) {
   press();
   toBeProcessed.push(s);
   //cout<<btn<<endl;
   if ((first>0)&&(second>0)&&(third>0)&&(fourth>0)) break;
  }
  cout<<first<<' '<<second<<' '<<third<<' '<<fourth<<endl;
  //found the LCM using findLCM.cpp
  return 0; 
}