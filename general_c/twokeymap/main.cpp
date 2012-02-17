
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string.h>
#include <stdint.h>
#include <sstream>

using namespace std;

class klass
{
public:
    klass(const string name);
    string getName(void) {return name_m;}
private:
    string name_m;
};

klass::klass(const string name)
{
    name_m = name;
}

class KeyKlass
{
public:
    enum
    {
        MAGIC_NUMBER = 0x4200CAFE,
        DEAD_INSTANCE = 0xDEAD
    };
    KeyKlass(const int key1, const int key2)
    {
        twoKey[0] = key1;
        twoKey[1] = key2;
        myMagic = MAGIC_NUMBER;
    }

    ~KeyKlass()
    {
        myMagic = DEAD_INSTANCE;
    }

    uint8_t getKey1() {return twoKey[0];}
    uint8_t getKey2() {return twoKey[1];}
    uint8_t * getKey() {return twoKey;}
    uint8_t twoKey[2];
    int64_t myMagic;
};

bool operator<(KeyKlass key1a, KeyKlass key1b)
{
    return memcmp(key1a.getKey(), key1b.getKey(), 2*sizeof(uint8_t)) < 0;
}

int main(int argc, char ** argv)
{
    map<KeyKlass, klass> klassMap;

    
    
    map<KeyKlass, klass>::iterator p;
    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            stringstream st;
            st << "Bob" << i << j;
            klassMap.insert(pair<KeyKlass, klass> (KeyKlass(i,j), klass(st.str())));
        }
    }
    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            stringstream st;
            st << "Bob" << i << j;
            p = klassMap.find(KeyKlass(i,j));
            printf("first key = %d, second key = %d\n", p->first.twoKey[0], p->first.twoKey[1]);
            if(st.str() != p->second.getName())
            {
                cout << "st = <" << st.str() << ">" << " value = <" << p->second.getName() << ">" << endl;
                cout << "failure" << endl;
                return EXIT_FAILURE;
            }
        }
    }
    
    p = klassMap.find(KeyKlass(2,1));
    if(p == klassMap.end())
    {
        cout << "Ooops this key does not exist" << endl;
        return 0;
    }
    //cout << "the name for id = " << p->first.twoKey << p->first.twoKey << " is " << p->second.getName() << endl;
    return 0;
}
