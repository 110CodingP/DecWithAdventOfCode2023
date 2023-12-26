#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

map<string,int> parse{
  {"one",1},
  {"two",2},
  {"three",3},
  {"four",4},
  {"five",5},
  {"six",6},
  {"seven",7},
  {"eight",8},
  {"nine",9},
  {"1",1},
  {"2",2},
  {"3",3},
  {"4",4},
  {"5",5},
  {"6",6},
  {"7",7},
  {"8",8},
  {"9",9},
  };

int main() {
  freopen("trebuchet.out","w",stdout);
  ifstream myFile;
  myFile.open("trebuchet.in");
  string myLine;
  int sum=0;
  if (myFile.is_open()) {
    while(myFile) {
      getline(myFile,myLine);
      vector<int> digit;
      for (int i=0;i<myLine.size();i++) {
        for (const auto& x: parse) {
          if (myLine.find(x.first)==i) {
            digit.push_back(parse.at(x.first));
            myLine[i]='^';
          }
        }
      }
      if (digit.size()>1) {
        sum+= digit[0]*10+digit[digit.size()-1];
      }
      else if (digit.size()==1){
        sum+= digit[0]*11;
      }
    }
  }
  cout<<sum;
  return 0;
}