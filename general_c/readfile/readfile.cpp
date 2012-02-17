
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>

using namespace std;

int readfileposix(string fileName)
{
   cout << "---posix----" << endl;
   char line[180] = "\0";
   int fd = open(fileName.c_str(), O_RDONLY);
   cout << "single read " << read(fd, line, sizeof(line)) << endl;
   cout << line;
   close(fd);
   cout << "---end posix----" << endl;
   return 0;
}

int readfilelibc(string fileName)
{
   cout << "---libc----" << endl;
   char line[180] = "\0";
   FILE *file_p = fopen(fileName.c_str(), "r");
   cout << "looped read" << endl;
   while(fgets(line, sizeof(line), file_p))
      cout << line;
   fclose(file_p);
   cout << "---end libc----" << endl;
   return 0;
}


