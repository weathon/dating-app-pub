#include <iostream>

// easy way to disable print 

float dis;
int INF = 1000000;
void sort(intArray array_, int start, int end, intArray &returnVector) {    
  intArray left, right;
  if (end - start == 1) {
    returnVector.push_back(array_[start]);//got you, it is not 0, but start
    return;
  }
  intArray array = intArray(array_.begin() + start, array_.begin() + end);
//   printa(array); 

  // printa(array);

  // https://stackoverflow.com/questions/50549611/slicing-a-vector-in-c
  sort(array, 0, array.size() / 2, left);
  sort(array, array.size() / 2, array.size(), right);
  // printa(left);
  // printa(right); //this is same as left, here is the problem, size=2, so size/2=1
  // sort(array, array.size()/2, array.size(), right);
  int left_pointer = 0, right_pointer = 0;
  left.push_back(INF);
  right.push_back(INF);
  for (auto _ : array) {
    // std::cout<<left[left_pointer]<<std::endl;
    if (left[left_pointer] == INF) {
      returnVector.push_back(right[right_pointer]);

      right_pointer++;
      continue;
    }
    if (right[right_pointer] == INF) {
      returnVector.push_back(left[left_pointer]);

      left_pointer++;
      continue;
    }


    if (left[left_pointer] <= right[right_pointer]) {
      returnVector.push_back(left[left_pointer]);
      left_pointer++;
    } else {
      dis += (left.size() - 1) - left_pointer; // because there is a inf there,
                                               // so minus 1, the code on stack?
      returnVector.push_back(right[right_pointer]);
      right_pointer++;
    }
  }
  // std::cout<<left.size()<<" "<<right.size()<<" "<<array.size()<<std::endl;
}

float compare(intArray a, intArray b) {
  // std::cout<<1<<std::endl;
  if (a.size() != b.size()) {
    std::cout << "What you are doing!!!" << std::endl;
  }
  int map[a.size()+100];
  // print("Size");
  // printa(a);
  for (int i = 0; i < b.size(); i++) {
    map[b[i]] = i;
  }
  for (int i = 0; i < a.size(); i++) {
    a[i] = map[a[i]];
  }
  dis = 0;
  intArray res;
  // for (auto _ : a)
  //   std::cout << _
  //             << " "; // got 102344 where it should be 10234? no,the last is ans
  // std::cout << std::endl;
  sort(a, 0, a.size(), res);
  // for (auto _ : res)
  //   std::cout << _ << " ";
  // print(dis);
  int n=a.size();
  return dis/(n*(n-1)/2);
}