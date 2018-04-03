#include <iostream>
#include <string>
#include <fcntl.h>
#include <fstream>
#include <string>
#include <stdexcept>  


using namespace std;

bool get_int_value(string filename, int &value)
{
    bool status = false;
    string the_line;
    ifstream file_stream (filename);
    if (file_stream.is_open())
    {
      if(getline (file_stream,the_line))
      {
        try{
            value = stoi(the_line);
            status = true;
        }
        catch(std::invalid_argument & e){
            cout << "invalid_argument: " << e.what() << endl;
        }
        catch(std::out_of_range & e){
            cout << "out_of_range: " << e.what() << endl;
        }
      } else 
      {
        cout << "invalid data\n";
      }
      file_stream.close();
    }

    return status;
}

int main(int argc, char *argv[])
{
    int value = -1;
    get_int_value("./test", value);
    std::cout << "int value = " << value << endl;
}


