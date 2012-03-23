#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(int argc, char *argv[])
{
   
    auto* i = new auto(1);
    cout << *i << endl;

  
    cout << typeid(i).name() << " as expected? "
	<< ((typeid(i) == typeid(int*)) ? "yes" : "no") << endl;

      
    vector<string> stv{"blah", "stuff"};
    for(auto i: stv)
      cout << i <<endl;
  
    auto * strauto = new auto(stv);
    cout << strauto->at(0) << " " << strauto->at(1) << endl;
  
    int times = 10;
    vector<int> vi = {1,2,3,4,5};
    for_each(vi.begin(), vi.end(), [&](int i) {
      cout << i*times << endl;
    });


}
