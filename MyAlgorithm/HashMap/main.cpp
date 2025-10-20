#include <iostream>
#include"HashMap.h"
using namespace std;

int main()
{
    HashMap<string, int> map;

    map.insert("apple", 10);
    map.insert("banana", 20);
    map.insert("cherry", 30);

    auto* value = map.find("banana");
    if (value)
    {
        cout << "found banana:" << *value << endl;
    }

    map.insert("apple", 99);

    map.remove("cherry");

    value = map.find("apple");
    if (value)
    {
        cout << "Apple:" << *value << endl;
    }

    map.debugPrint();

    cout << "size:" << map.getSize() << ",buckets:" << map.getBucketCount() << endl;
}

