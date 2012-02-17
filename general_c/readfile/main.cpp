#include <iostream>

using namespace std;

extern int readfileposix(string fileName);
extern int readfilelibc(string fileName);

using namespace std;

int main(int argc, char ** argv)
{
   readfileposix("textfile");
   readfilelibc("textfile");
   return 0;
}

