#include <iostream>
#include"HashMap.h"
using namespace std;

int main()
{
    HashMap<string, int> map;

    map.insert("apple1", 10);
    map.insert("banana", 20);
    map.insert("cherry", 30);
    map.insert("apple2", 99);


    map.debugPrint();

    cout << "size:" << map.getSize() << ",buckets:" << map.getBucketCount() << endl;
}

