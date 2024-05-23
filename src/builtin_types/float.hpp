#include <vector>
#include "type.hpp"
#include "object.hpp"

#ifndef BUILTIN_TYPES_FLOAT_HPP_
#define     BUILTIN_TYPES_FLOAT_HPP_

class FloatType: TypeObj {
public:
    const static ObjRef float_type_obj;

    ObjRef operator()(std::vector<ObjRef> args) const override;

private:
    FloatType(): TypeObj {"float", getMetatypeObject()} {}
};

class FloatObject : public Object
{
public:
    static ObjRef getFloatObject(float value) { return ObjRef{new FloatObject{value}}; }

    double getValue() const { return _value; }

private:
    double _value;

    FloatObject(double value) : Object {FloatType::float_type_obj}, _value{value} {}
};

#endif