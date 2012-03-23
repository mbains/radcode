#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>
#include <algorithm>
#include "signals.h"


using namespace std;

void test(int a, int b) {
    cout << "test function: " << a << " " << b << "\n";
}

class Fun {

public:
    int id;
    void run(int a, int b) {
        cout << "Fun, ID: " << id << " - run " << a << " " << b << "\n";
    }
};

int main(int argc, char *argv[])
{
   
    Fun f = {id: 5};
    signals::Signal<int, int> onEvent;
    signals::Signal<int, int> event2;

    onEvent.bind([&](int a, int b) {
        std::cout << "Event triggered " << a << ", " << b << "\n";
    });
    

    auto  handler = std::bind(&Fun::run, f, std::placeholders::_1, std::placeholders::_2);
    onEvent.bind(handler);

    onEvent.bind(test);

    Fun f2 = {id: 10};
    event2.bind( std::bind(&Fun::run, f2, std::placeholders::_1, std::placeholders::_2));

    event2.trigger(20, 30);
    
    onEvent.trigger(10, 20);

}
