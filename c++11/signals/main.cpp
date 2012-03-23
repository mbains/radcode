#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>
#include <algorithm>
#include "signals.h"


using namespace std;

void test() {
    cout << "test function\n";
}

class Fun {
public:
    void run(int a, int b) {
        cout << "fun run " << a << " " << b << "\n";
    }
};

int main(int argc, char *argv[])
{
   
    Fun f;
    signals::Signal<int, int> onEvent;
    
    onEvent.bind([&](int a, int b) {
        std::cout << "Event triggered " << a << ", " << b << "\n";
	test();
	f.run(a, b);
    });
    

    auto  handler = std::bind(&Fun::run, f);
    //onEvent.bind(&handler); //this does not work
    
    onEvent.trigger(10, 20);

}
