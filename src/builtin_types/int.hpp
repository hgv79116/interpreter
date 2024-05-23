#include <vector>
#include "type.hpp"
#include "object.hpp"

#ifndef BUILTIN_TYPES_INT_HPP_
#define     BUILTIN_TYPES_INT_HPP_

class IntType: TypeObj {
public:
    const static ObjRef int_type_obj;

    ObjRef operator()(std::vector<ObjRef> args) const override;

private:
    IntType(): TypeObj {"int", getMetatypeObject()} {}
};

class IntObject : public Object
{
public:
    /**
     * Static creation method to abstract away constructor. Might be used
     * for future interning
    */
    static ObjRef getIntObject(int value) { return ObjRef{new IntObject{value}}; }

    int getValue() const { return _value; }

private:
    int _value;

    IntObject(int value) : Object {IntType::int_type_obj}, _value{value} {}
};

#endif