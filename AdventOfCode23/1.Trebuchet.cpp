#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

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
        int ch=(int) myLine[i];
        if (ch>=48&&ch<=57) {
          ch=ch-48;
          digit.push_back(ch);
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