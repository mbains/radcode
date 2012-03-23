#ifndef __signals_h__
#define __signals_h__

#include <list>
#include <memory>
#include <iostream>
#include <functional>

namespace signals {
    template<typename... Values> class Signal {
    private:
        std::list<std::function<void(Values...)>> fns;
    public:
        void bind(std::function<void(Values...)> fn) {
            fns.push_back(fn);
        }
        void trigger(Values... values) {
            for (auto it = fns.begin(); it != fns.end(); ++it) {
                (*it)(values...);
            }
        }
    };
}

// Example
// signals::Signal<int, int> onEvent;
// 
// onEvent.bind([](int a, int b) {
//     std::cout << "Event triggered " << a << ", " << b << "\n";
// });
// 
// onEvent.trigger(10, 20);

#endif


