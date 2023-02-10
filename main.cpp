#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <hashtable.h>
#include <iostream>
#include <string>
#include <vector>

#define LEN 30
int N = number_of_objects
#define print(x) std::cout << x << std::endl;
#define printa(x)                                                              \
  for (auto thisiscool : x)                                                    \
    std::cout << thisiscool << " ";                                            \
  std::cout << std::endl;
#include "ADT.hpp"
    using namespace std;


#define ifNULL(x) if (x == NULL)
// #define print(x, y) cout << x << " " << y << endl;

floatArray maxPerArg(floatArray list1, floatArray list2) {
  if (list1.size() != list2.size()) {
    cout << "Error: Lists are not the same size" << endl;
    return list2;
  }
  for (int i = 0; i < list1.size(); i++) {
    if (list1[i] > list2[i]) {
      list2[i] = list1[i];
    }
  }
  return list2;
}

floatArray minPerArg(floatArray list1, floatArray list2) {
  if (list1.size() != list2.size()) {
    cout << "Error: Lists are not the same size" << endl;
    return list2;
  }
  for (int i = 0; i < list1.size(); i++)

  {
    if (list1[i] < list2[i]) {
      list2[i] = list1[i];
    }
  }
  return list2;
}

long long Callcount;

bool cmp(dataPoint list1, dataPoint list2) {
  // by copolit
  return list1.distanceFromDad < list2.distanceFromDad;
}

void getData(vector<dataPoint> myArray, float &theMax, float &theMin,
             float &inner, float &outer) {
  sort(myArray.begin(), myArray.end(), cmp);
  theMax = myArray[myArray.size() - 1].distanceFromDad;
  theMin = myArray[0].distanceFromDad;
  inner = myArray[myArray.size() / 2 - 1].distanceFromDad;
  outer = myArray[myArray.size() / 2].distanceFromDad;
  // cout<<"min"<<theMin<<endl;
}

void ConstructBallTree(BallTreeNode *BT, vector<dataPoint> localobjetcs) {
  // cout<<localobjetcs[0].ancestorsDistancesList.size()<<endl;
  ifNULL(BT) {
    cout << "Error: Null pointer; line 119" << endl;
    return;
  }
  if (localobjetcs.size() == 0) {
    cout << "where is this" << endl;
    return;
  }
  if (localobjetcs.size() == 1) {
    BT->myobject = localobjetcs.at(0);
    BT->inner = 0;
    BT->outer = 0;
    BT->count = 1;
    BT->left = 0;
    BT->right = 0;
    return;
  }

  int selectedIndex = rand() % localobjetcs.size();
  swap(localobjetcs[localobjetcs.size() - 1], localobjetcs[selectedIndex]);
  BT->myobject = localobjetcs.at(localobjetcs.size() - 1);
  // print(localobjetcs[0].data.size()) //why all 0
  localobjetcs.pop_back();

  for (int i = 0; i < localobjetcs.size(); i++) {
    localobjetcs[i].distanceFromDad =
        d((BT->myobject), localobjetcs[i], Callcount);
    localobjetcs[i].ancestorsDistancesList.push_back(
        localobjetcs[i].distanceFromDad);
  }
  float a;
  getData(localobjetcs, BT->myobject.max, BT->myobject.min, BT->inner,
          BT->outer);
  vector<dataPoint> L;
  vector<dataPoint> R;

  for (int i = 0; i < localobjetcs.size(); i++) {
    if (localobjetcs[i].distanceFromDad <= BT->inner) {
      L.push_back(localobjetcs[i]);
    } else if (localobjetcs[i].distanceFromDad >= BT->outer) {
      R.push_back(localobjetcs[i]);
    } else {
      cout << "I think I am lost, can someone help me?" << endl;
    }
  }
  BT->count = localobjetcs.size();
  if (L.size() != 0) {
    BallTreeNode *tmp = new BallTreeNode;
    ifNULL(tmp) {
      cout << "Error: Null pointer; line 181" << endl;
      return;
    }
    ConstructBallTree(tmp, L);
    BT->left = tmp;
  } else {
    // forgot this
    BT->left = NULL;
  }
  if (R.size() != 0) {
    BallTreeNode *tmp2 = new BallTreeNode;
    ifNULL(tmp2) {
      cout << "Error: Null pointer; line 196" << endl;
      return;
    }
    ConstructBallTree(tmp2, R);
    BT->right = tmp2;
  } else {
    BT->right = NULL;
  }
}

void generateCMTData(BallTreeNode *BT, floatArray &returnNear,
                     floatArray &returnFar) {
  floatArray Lnear, Lfar, Rnear, Rfar;
  if (BT->left) // by copilot
  {
    generateCMTData(BT->left, Lnear, Lfar);
  }
  if (BT->right) {
    generateCMTData(BT->right, Rnear, Rfar);
  }
  // cout<<1<<endl;
  if (Lnear.size() != 0 && Rnear.size() != 0) {
    Lnear.pop_back();
    Lfar.pop_back();
    Rnear.pop_back();
    Rfar.pop_back();
    BT->myobject.nears =
        minPerArg(minPerArg(Lnear, Rnear), BT->myobject.ancestorsDistancesList);
    BT->myobject.fars =
        maxPerArg(maxPerArg(Lfar, Rfar), BT->myobject.ancestorsDistancesList);
  } else if (Lnear.size() != 0 and Rnear.size() == 0) {
    Lnear.pop_back();
    Lfar.pop_back();
    BT->myobject.nears = minPerArg(Lnear, BT->myobject.ancestorsDistancesList);
    BT->myobject.fars = maxPerArg(Lfar, BT->myobject.ancestorsDistancesList);
  } else if (Rnear.size() != 0 and Lnear.size() == 0) {
    Rnear.pop_back();
    Rfar.pop_back();
    BT->myobject.nears = minPerArg(Rnear, BT->myobject.ancestorsDistancesList);
    BT->myobject.fars = maxPerArg(Rfar, BT->myobject.ancestorsDistancesList);
  } else {
    BT->myobject.nears = BT->myobject.ancestorsDistancesList;
    BT->myobject.fars = BT->myobject.ancestorsDistancesList;
  }
  returnNear = BT->myobject.nears;
  returnFar = BT->myobject.fars;
}

// array modified? poped? xkoukouke meiyanzheng
void printCMTFars(BallTreeNode BT) {
  cout << BT.myobject.nears.size() << endl;
  if (BT.left) {
    printCMTFars(*BT.left);
  }
}

void BaselineSearchRadius(BallTreeNode *BT, dataPoint ObjectQ, float r,
                          vector<dataPoint> &returnObjects) {
  ifNULL(BT) { return; }
  float dis = d(BT->myobject, ObjectQ, Callcount);
  if (dis <= r) {
    returnObjects.push_back(BT->myobject);
  }

  if (dis > BT->myobject.max) {
    if (dis - BT->myobject.max > r) {
      return;
    }
  }

  if (dis < BT->myobject.min) {
    if (BT->myobject.min - dis > r) {
      return;
    }
  }

  if (dis + r >= BT->outer) {
    BaselineSearchRadius(BT->right, ObjectQ, r,
                         returnObjects); // this should be right copilot!!
  }
  if (dis - r <= BT->inner) {
    BaselineSearchRadius(BT->left, ObjectQ, r, returnObjects);
  }
}

float maxPD(floatArray mystack, BallTreeNode &node) {
  if (mystack.size() != node.myobject.fars.size()) {
    cout << "Error: stack size not equal to nearest distance size" << endl;
    return -1;
  }
  float ans = 0;
  for (int i = 0; i < mystack.size(); i++) {
    if (node.myobject.fars.at(i) < mystack[i]) {
      ans = (mystack[i] - node.myobject.fars[i] > ans)
                ? mystack[i] - node.myobject.fars[i]
                : ans;
    } else if (node.myobject.nears.at(i) > mystack[i]) {
      ans = (node.myobject.nears[i] - mystack[i] > ans)
                ? node.myobject.nears[i] - mystack[i]
                : ans;
    }
  }
  return ans;
}

vector<float> gobalstack;
void CMTSearchRadius(BallTreeNode *BT, dataPoint ObjectQ, float r,
                     vector<dataPoint> &returnObjects) {
  ifNULL(BT) { return; }
  // if(gobalstack.size()!=0)
  //     cout << gobalstack[gobalstack.size()-1] << endl;

  if (maxPD(gobalstack, *BT) > r) {
    // print(r, dis);
    return;
  }
  float dis = d(BT->myobject, ObjectQ, Callcount);

  if (dis <= r) {
    returnObjects.push_back(BT->myobject);
  }

  if (dis > BT->myobject.max) {
    if (dis - BT->myobject.max > r) {
      return;
    }
  }

  if (dis < BT->myobject.min) {
    if (BT->myobject.min - dis > r) {
      return;
    }
  }
  // cout<<dis<<endl;

  gobalstack.push_back(dis);
  if (dis + r >= BT->outer) {
    CMTSearchRadius(BT->right, ObjectQ, r, returnObjects);
  }
  if (dis - r <= BT->inner) {
    CMTSearchRadius(BT->left, ObjectQ, r, returnObjects);
  }
  gobalstack.pop_back();
}

vector<dataPoint> Objects(N);
int main() {
  cout << "Generating data points" << endl;
  genData(Objects);
  cout << "data points generated" << endl;
  BallTreeNode *rootNewBT = new BallTreeNode;
  if (rootNewBT == NULL) {
    cout << "Error: Memory allocation failed" << endl;
    return 1;
  }

  auto start = chrono::high_resolution_clock::now();
  // print(Objects[0].data.size())// 0 here how
  ConstructBallTree(rootNewBT, Objects);
  auto end = chrono::high_resolution_clock::now();
  cout << "C++ Tree Build Time: "
       << chrono::duration_cast<chrono::microseconds>(end - start).count() /
              1000.0
       << endl;

  floatArray a, b;
  vector<dataPoint> ans;
  dataPoint newObject;
  newObject.data = Objects[1].data; // randomArray(2);

  start = chrono::high_resolution_clock::now();
  generateCMTData(rootNewBT, a, b);
  end = chrono::high_resolution_clock::now();
  cout << "C++ Generate CMT Data Time: "
       << chrono::duration_cast<chrono::microseconds>(end - start).count() /
              1000.0
       << endl;

  // printCMTFars(*rootNewBT);
  Callcount = 0;
  floatArray range({0, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13,
                    0.14, 0.15, 0.16, 0.17});
  cout << "Model Name, Language, r, nFound, Call Counts, Time, N, LEN" << endl;
  // for (auto r : range)
  // {
  //     Callcount = 0;
  //     ans.clear(); // inside
  //     start = chrono::high_resolution_clock::now();
  //     for (int _ = 0; _ < 5; _++)
  //         BaselineSearchRadius(rootNewBT, Objects[_ * 10], r, ans);
  //     end = chrono::high_resolution_clock::now();
  //     cout << "Baseline Real,C++," << r << "," << ans.size()/5 << "," <<
  //     Callcount/5 << "," << chrono::duration_cast<chrono::microseconds>(end -
  //     start).count() / 1000.0/5<<","<<N; cout << endl;
  // }

  for (auto r : range) {
    for (int _ = 0; _ < 5; _++) {
      Callcount = 0; //inside or outside
      ans.clear();
      start = chrono::high_resolution_clock::now();
      CMTSearchRadius(rootNewBT, Objects[_ * 10], r, ans);
      end = chrono::high_resolution_clock::now();
      cout << "CMT Real,C++," << r << "," << ans.size() << ","
           << Callcount << ","
           << chrono::duration_cast<chrono::microseconds>(end - start).count() /
                  1000.0
           << "," << N<<","<<LEN;
      cout << endl;
    }
  }

  // for (auto r : range)
  // {
  //     ans.clear();
  //     Callcount = 0;
  //     start = chrono::high_resolution_clock::now();
  //     for (int _ = 0; _ < 5; _++)

  //         for (int i = 0; i < Objects.size(); i++)
  //         {
  //             if (d(Objects[i], Objects[_ * 10], Callcount) <= r)
  //             {
  //                 ans.push_back(Objects[i]);
  //             }
  //         }
  //     end = chrono::high_resolution_clock::now();
  //     cout << "BF Real,C++," << r << "," << ans.size()/5 << "," <<
  //     Callcount/5 << "," << chrono::duration_cast<chrono::microseconds>(end -
  //     start).count() / 1000.0/5<<","<<N;
  //     // cout << "Baseline r=" << r << " " << ans.size() << " " << Callcount
  //     << endl;
  //     // cout << "C++ search CMT Time: " <<
  //     chrono::duration_cast<chrono::microseconds>(end - start).count() /
  //     1000.0 << endl; cout << endl;
  // }

  return 0;
}