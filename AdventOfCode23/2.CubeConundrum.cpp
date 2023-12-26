#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

int power(int a,int b) {
  if (b==0) return 1;
  return (a*power(a,b-1));
}

map<char,int> parse{
  {'1',1},
  {'2',2},
  {'3',3},
  {'4',4},
  {'5',5},
  {'6',6},
  {'7',7},
  {'8',8},
  {'9',9},
  };
map<string,int> clrs{
  {"red",0},
  {"green",1},
  {"blue",2}
};

int main() {
  freopen("cube.out","w",stdout);
  ifstream myFile;
  myFile.open("cube.in");
  string myLine;
  int valid=0;
  vector<int> max_val{12,13,14};
  if (myFile.is_open()) {
    while (myFile) {
      getline(myFile,myLine);
      int game_num=0;
      vector<int> g_no;
      if (myLine.find(" ")!=string::npos) 
      {int i1=myLine.find(" ");
      myLine[i1]='&';
      int i2=myLine.find(":");
      for (int i=i1+1;i<i2;i++) {
        g_no.push_back(parse.at(myLine[i]));
      }
      for (int i=0;i<g_no.size();i++) {
        game_num += g_no[i]*power(10,g_no.size()-i-1);
      }
      vector<int> cube;

      while(myLine.find(" ")!=string::npos) {
        vector<int> num;
        int idx=myLine.find(" ");
        myLine[myLine.find(" ")]= '&';
        int idx2=myLine.find(" ");
        myLine[myLine.find(" ")]= '&';

        for (int i=idx+1;i<idx2;i++) {
          num.push_back(parse[myLine[i]]);
        }
        int number=0;
        for (int i=0;i<num.size();i++) {
          number += num[i]*power(10,num.size()-i-1);
          
        }
        cube.push_back(number);
      }

      vector<int> colours;
      for (int i=0;i<myLine.size();i++) {
        for(const auto& c: clrs) {
          if (myLine.find(c.first)==i) {
            colours.push_back(c.second);
            myLine[i]='^';
          }
        }
      }
      bool is_valid=true;
      for (int i=0;i<colours.size();i++) {
        if (cube[i]>max_val[colours[i]]) {
          is_valid=false;
        }
      }
      if (is_valid) {
        valid+=game_num;
      }
      }
    }
  }
  cout<<valid;
  myFile.close();
  return 0;
}