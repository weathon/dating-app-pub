#include <iostream>
#include <vector>
typedef std::vector<float> floatArray;
typedef std::vector<int> intArray;
#include "distance.hpp"


struct dataPoint
{
    intArray data;
    int id;
    floatArray ancestorsDistancesList;
    float distanceFromDad;
    float max = 0;
    float min = 0;
    floatArray fars = {};
    floatArray nears = {};
};

struct BallTreeNode
{
    dataPoint myobject;
    BallTreeNode *left;
    BallTreeNode *right;
    float inner = 0;
    float outer = 0;
    int count = 0;
};

intArray randomArray(int size)
{
    // by copolit
    intArray list;
    int tmp, rnd, rnd2;
    for (int i = 0; i < size; i++)
    {
        list.push_back(i);
    }

    for (int i = 0; i < 8; i++) //too slow becasue it did not swap at all
    {
        rnd = rand()%size;
        rnd2 = rand()%size;
        tmp=list[rnd];
        list[rnd]=list[rnd2];
        list[rnd2]=tmp;
    }
    return list;
}

float d(dataPoint list1, dataPoint list2, long long & Callcount)
{
        Callcount++;
        // int sum=0;
        // for(int i=0; i<list1.data.size(); i++)
        // {
        //     sum+=(list1.data[i]-list2.data[i])*(list1.data[i]-list2.data[i]);
        // }
        // return sum/50;
        return compare(list1.data, list2.data);
}

void genData(std::vector<dataPoint> &Objects) // no wonder it is 0, this is vector not array
{
    for (int i = 0; i < N; i++)
    {
        Objects[i].data = randomArray(LEN);
        // print(Objects[i].data.size());
        Objects[i].id = i;
    }
}