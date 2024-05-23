#include <vector>
#include <string>
#include "object.hpp"

#ifndef CALLABLE_HPP_
#define     CALLABLE_HPP_

class Callable: public Object {
public:
    virtual ObjRef call(std::vector<ObjRef> args) = 0;
};

#endif