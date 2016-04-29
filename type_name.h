#ifndef __TYPE_NAME_H__
#define __TYPE_NAME_H__

// http://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c

#include <type_traits>
#include <typeinfo>
#include <string>
#include <memory>
#include <cxxabi.h>


template <class T> std::string type_name() {
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
            (
            abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                nullptr, nullptr), std::free );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value) r += " const";
    if (std::is_volatile<TR>::value) r += " volatile";
    if (std::is_lvalue_reference<T>::value) r += "&";
    else if (std::is_rvalue_reference<T>::value) r += "&&";
    return r;
}


#endif //__TYPE_NAME_H__
