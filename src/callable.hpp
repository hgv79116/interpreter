#include <vector>
#include <string>
#include "object.hpp"

class Callable: public Object {
public:
    virtual ObjRef call(std::vector<ObjRef> args) = 0;
};