#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
using namespace std;
vector<string> strsplit(string str, string delim){
    int prevInd = 0;
    vector<string> toReturn;
    int sz=str.size();
    for(int i = 0; i < sz; i++){
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
  ifstream myFile;
  myFile.open("7.Part1.in");
  vector<pair<string,int>> five;
  vector<pair<string,int>> four;
  vector<pair<string,int>> full;
  vector<pair<string,int>> three;
  vector<pair<string,int>> two;
  vector<pair<string,int>> one;
  vector<pair<string,int>> high;
  string myLine;
  if (myFile.is_open()) {
    while(myFile) {
      getline(myFile,myLine);
      vector<string> line=strsplit(myLine," ");
      string hand=line[0];
      while (find(hand.begin(),hand.end(),'A')!=hand.end())  *find(hand.begin(),hand.end(),'A')='9'+5;
      while (find(hand.begin(),hand.end(),'K')!=hand.end())  *find(hand.begin(),hand.end(),'K')='9'+4;
      while (find(hand.begin(),hand.end(),'Q')!=hand.end())  *find(hand.begin(),hand.end(),'Q')='9'+3;
      while (find(hand.begin(),hand.end(),'J')!=hand.end())  *find(hand.begin(),hand.end(),'J')='1';
      while (find(hand.begin(),hand.end(),'T')!=hand.end())  *find(hand.begin(),hand.end(),'T')='9'+1;
      //cout<<hand<<endl;
      if (hand=="*") break;
      int bid=stoi(line[1]);
      string hand_cpy=hand;
      sort(all(hand_cpy));
      int max_len=0;
      int same=0;
      int sz=hand.size();
      //cout<<sz<<endl;
      int curr_len=0;
      int ct_J=0;
      for (int i=0;i<sz-1;i++) {
        if (hand_cpy[i]=='1') ct_J++;
        if (curr_len==0&&hand_cpy[i]==hand_cpy[i+1]) {
          curr_len++;
          same++;
          if (hand_cpy[i+1]=='1') {curr_len--;same--;}
        }
        else if (hand_cpy[i]==hand_cpy[i+1]) {
          curr_len++;
          if (hand_cpy[i]=='1') curr_len--;
        }
        else if (hand_cpy[i]!=hand_cpy[i+1]) {
          max_len=max(curr_len,max_len);
          curr_len=0;
        }
      }
      max_len=max(curr_len,max_len);
      max_len++;
      max_len+=ct_J;
      if (same==0&&max_len>1) same++;
      if (max_len==1) high.push_back({hand,bid});
      else if (max_len==2&&same==1) one.push_back({hand,bid});
      else if (max_len==2&&same==2) two.push_back({hand,bid});
      else if (max_len==3&&same==1) three.push_back({hand,bid});
      else if (max_len==3&&same==2) full.push_back({hand,bid});
      else if (max_len==4&&same==1) four.push_back({hand,bid});
      else if (max_len==5&&same==1) five.push_back({hand,bid});
    }
  }
  sort(all(high));
  sort(all(one));
  sort(all(two));
  sort(all(three));
  sort(all(full));
  sort(all(four));
  sort(all(five));
  int winnings=0;
  int start=0;
  int sz=high.size();
  for (int i=1;i<=sz;i++) {
    winnings+= high[i-1].second*(i+start);
    //cout<<high[i-1].second<<endl;
  }
  start+=sz;
  sz=one.size();
  for (int i=1;i<=sz;i++) {
    winnings+= one[i-1].second*(i+start);
    //cout<<one[i-1].second<<endl;
  }
  start+=sz;
  sz=two.size();
  for (int i=1;i<=sz;i++) {
    winnings+= two[i-1].second*(i+start);
    //cout<<two[i-1].second<<endl;
  }
  start+=sz;
  sz=three.size();
  for (int i=1;i<=sz;i++) {
    winnings+= three[i-1].second*(i+start);
    //cout<<three[i-1].second<<' '<<three[i-1].first<<endl;
  }
  start+=sz;
  sz=full.size();
  for (int i=1;i<=sz;i++) {
    winnings+= full[i-1].second*(i+start);
    //cout<<full[i-1].second<<"@"<<endl;
  }
  start+=sz;
  sz=four.size();
  for (int i=1;i<=sz;i++) {
    winnings+= four[i-1].second*(i+start);
    //cout<<four[i-1].second<<' '<<four[i-1].first<<endl;
  }
  start+=sz;
  sz=five.size();
  for (int i=1;i<=sz;i++) {
    winnings+= five[i-1].second*(i+start);
    //cout<<five[i-1].second<<' '<<five[i-1].first<<endl;
  }
  cout<<winnings<<endl;
  return 0;
}