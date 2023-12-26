#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

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
  freopen("cube2.out","w",stdout);
  ifstream myFile;
  myFile.open("cube.in");
  string myLine;
  int product=0;
  if (myFile.is_open()) {
    while (myFile) {
      vector<vector<int>> max_val;
      max_val.resize(3);
      getline(myFile,myLine);
      if (myLine.find(" ")!=string::npos) {
        int i1=myLine.find(" ");
        myLine[i1]='&';
        int i2=myLine.find(":");
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
        for (int i=0;i<colours.size();i++) {
          max_val[colours[i]].push_back(cube[i]);
        }
        for (int i=0;i<3;i++) {
          sort(max_val[i].begin(),max_val[i].end());
        }
        int red_max=max_val[0].back();
        int green_max=max_val[1].back();
        int blue_max=max_val[2].back();
        int power_of_set= red_max*green_max*blue_max;
        product += power_of_set;
        // cout<<power_of_set<<endl;
      }
    }
  }
  cout<<product;
  myFile.close();
  return 0;
}