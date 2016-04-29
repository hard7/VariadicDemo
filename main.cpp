#include <iostream>
#include <vector>
#include "type_name.h"

using std::cout;
using std::endl;

struct _A {
    ~_A() { cout << "~_A" << endl; }
};

std::ostream& operator << (std::ostream& os, _A const&) {
    return os << "string(_A)";
}

void func(std::vector<void*>& _x) {
    cout << *static_cast<_A*>(_x[0]) << endl;
    cout << *static_cast<float*>(_x[1]) << endl;
}

template <typename U>
void run_(std::vector<void*>& vec, U & u) {
    cout << "type_name: " << type_name<U>() << " [" << &u << "] "<< endl;
    vec.push_back(&u);
}

template <typename U, typename... Args>
void run_(std::vector<void*> & vec, U & u, Args & ... args) {
    cout << "type_name: " << type_name<U>() << " [" << &u << "] "<< endl;
    vec.push_back(&u);
    run_(vec, ( args ) ...);
}

template <typename... Args>
void run(Args && ... args) {
    std::vector<void*> vec;
    run_(vec, args...);
    func(vec);
}


int main() {
    {
        run(_A(), 5.2f);
    }

    cout << endl;
    {
        _A a;
        run(_A(), 5.8f);
    }
    return 0;
}