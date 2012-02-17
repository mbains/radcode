#include <iostream>
#include <string.h>

using namespace std;

char * strcopy(char * StringIn)
{ 
  char * stringGenerated;
  int size = 1;
  while(StringIn[size] != '\0')
        size++;

  stringGenerated = new char[size];   
  for(int i = 0; i < size; i++)
  {
     stringGenerated[i] = StringIn[i];
  }
  cout << "generated string is " << stringGenerated << endl;
  return stringGenerated;
}

int main()
{
  char s1[80], s2[80];
  char *s3;    
  strcpy(s1, "haha");
  cout << "sizeof(s1): " << sizeof(s1) 
      << " sizeof(s2): " << sizeof(s2) << endl; 
  strcpy(s2,s1);
  cout << "after copying" << endl;
  cout << "sizeof(s1): " << sizeof(s1)
        << " sizeof(s2): " << sizeof(s2) << endl;
  s3 = strcopy(s1);
  cout << "s3: " << s3 << endl
       << "sizeof(s3) = " << sizeof(s3) << endl;
  return 0;     
}


