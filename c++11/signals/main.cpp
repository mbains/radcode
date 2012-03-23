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

class Klass {

public:
    int id;
    void run(int a, int b) {
        cout << "Klass, ID: " << id << " - run " << a << " " << b << "\n";
    }
    void runWithExtraArgs(string str, int a, int b) {

        cout << "Klass, ID: " << id << " - runWithExtraArgs " << str << " " << a << " " << b << "\n";
    }
};

int main(int argc, char *argv[])
{
   
    Klass f = {id: 5};
    signals::Signal<int, int> event1;
    signals::Signal<int, int> event2;

    event1.bind([&](int a, int b) {
        std::cout << "Event triggered " << a << ", " << b << "\n";
    });
    

    auto  handler = bind(&Klass::run, f, placeholders::_1, placeholders::_2);
    event1.bind(handler);

    event1.bind(test);

    Klass f2 = {id: 10};
    event2.bind( bind(&Klass::run, f2, placeholders::_1, placeholders::_2));

    event2.trigger(20, 30);
    
    event1.trigger(10, 20);

    event2.bind( bind(&Klass::runWithExtraArgs, f, "Stuff", placeholders::_1, placeholders::_2));

    event2.trigger(100, 200);

}
