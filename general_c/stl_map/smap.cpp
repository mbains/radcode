/* 
 * File:   smap.cpp
 * Author: mbai
 *
 * Created on February 24, 2011, 9:05 AM
 */

#include <cstdlib>
#include <iostream>
#include <string.h>
#include <map>
using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {

   typedef enum {
      
      MONDAY,
      TUESDAY,
      WEDNESDAY,
      THURSDAY,
      FRIDAY,
      SATURDAY,
      SUNDAY
   }days_t;

   typedef map<int, string> mainMap_t;
   typedef mainMap_t::iterator mainMapIter_t;
   typedef mainMap_t::value_type mainMapValue_t;
   mainMap_t mainMap;
   string word;

   mainMap.insert(mainMapValue_t(MONDAY, "Monday"));
   mainMap.insert(mainMapValue_t(TUESDAY, "Tuesday"));
   mainMap.insert(mainMapValue_t(WEDNESDAY, "Wednesday"));
   mainMap.insert(mainMapValue_t(THURSDAY, "Thursday"));
   mainMap.insert(mainMapValue_t(FRIDAY, "Fri"));
   mainMap.insert(mainMapValue_t(SATURDAY, "Sat"));
   mainMap.insert(mainMapValue_t(SUNDAY, "Sun"));
   
   for(mainMapIter_t i = mainMap.begin(); i != mainMap.end(); i++)
   {
      cout << i->first << " " << i->second << endl;
   }

   mainMapIter_t i = mainMap.begin();
   i = mainMap.find(MONDAY);
   cout << "Monday " << i->second << endl;
   
   return 0;
}

