#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>


using namespace std;
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


int power(int b,int e) {
  if (e==0) {
    return 1;
  } 
  return (b*power(b,e-1));
}


int main() {
  freopen("gear.out","w",stdout);
  ifstream myFile;
  myFile.open("gear.in");
  int sum=0;
  vector<pair<int,int>> added;
  int line1=0;
  int line2=1;
  int dummy=1;
  if (true) {
    while (dummy==1) {
      string myLine1="...*......";
      string myLine2="..35..633.";
      //Symbols in Line1
      for (int i=0;i<myLine1.size();i++) {
        if (myLine1[i]=='.') continue;
        if (!(myLine1[i]>=48&&(myLine1[i]<=57))) {
          //line 1 numbers
          for (int j=i-1;j>=0;j--) {
            if (!((myLine1[j]>=48)&&(myLine1[j]<=57))) {
              break;
            }
            if (find(added.begin(),added.end(),make_pair(line1,j))!=added.end()) {
              break;}
            sum+=parse[myLine1[j]]*power(10,i-j-1);
            added.push_back({line1,j});
          }
          vector<int> fwd_num;
          for (int j=i+1;j<myLine1.size();j++) {
            if (!((myLine1[j]>=48)&&(myLine1[j]<=57))) {
              break;
            }
            if (find(added.begin(),added.end(),make_pair(line1,j))!=added.end()) {break;}
            fwd_num.push_back(parse[myLine1[j]]);
            added.push_back({line1,j});
          }
          for (int j=0;j<fwd_num.size();j++) {
            sum+=fwd_num[j]*power(10,fwd_num.size()-j-1);
          }

          //line2 numbers
          for (int j=i-1;j>=0;j--) {
            if (!((myLine2[j]>=48)&&(myLine2[j]<=57))) {
              break;
            }
            if (find(added.begin(),added.end(),make_pair(line2,j))!=added.end()) {break;}
            sum+=parse[myLine2[j]]*power(10,i-j-1);
            added.push_back({line2,j});
          }
          vector<int> fwd_num2;
          for (int j=i+1;j<myLine2.size();j++) {
            if (!((myLine2[j]>=48)&&(myLine2[j]<=57))) {
              break;
            }
            if (find(added.begin(),added.end(),make_pair(line2,j))!=added.end()) {break;}
            fwd_num2.push_back(parse[myLine1[j]]);
            added.push_back({line2,j});
          }
          for (int j=0;j<fwd_num2.size();j++) {
            sum+=fwd_num2[j]*power(10,fwd_num2.size()-j-1);
          }
        }
      }
      //Symbols in Line2
      for (int i=0;i<myLine2.size();i++) {
        if (myLine2[i]=='.') continue;
        if (!((myLine2[i]>=48)&&(myLine2[i]<=57))) {
          //in line1
          for (int j=i-1;j>=0;j--) {
            if (!((myLine1[j]>=48)&&(myLine1[j]<=57))) {
              break;
            }
            if (find(added.begin(),added.end(),make_pair(line1,j))!=added.end()) {
              break;}
            sum+=parse[myLine1[j]]*power(10,i-j-1);
            added.push_back({line1,j});
          }
          vector<int> fwd_num3;
          for (int j=i+1;j<myLine1.size();j++) {
            if (!((myLine1[j]>=48)&&(myLine1[j]<=57))) {
              break;
            }
            if (find(added.begin(),added.end(),make_pair(line1,j))!=added.end()) {break;}
            fwd_num3.push_back(parse[myLine1[j]]);
            added.push_back({line1,j});
          }
          for (int j=0;j<fwd_num3.size();j++) {
            sum += fwd_num3[j]*power(10,fwd_num3.size()-j-1);
          }
        }
      }
      myLine1=myLine2;
      line1++;
      line2++;
      dummy++;
    }
  }
  cout<<sum;
  return 0;
}