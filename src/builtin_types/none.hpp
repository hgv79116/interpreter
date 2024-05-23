#include <vector>
#include "type.hpp"
#include "object.hpp"

#ifndef BUILTIN_TYPES_NONE_HPP_
#define     BUILTIN_TYPES_NONE_HPP_

/**
 * Underlying C++ type for class 'NoneType'.
*/
class NoneType: TypeObj {
public:
    /* Singleton representing 'NoneType' type. Result of type(None). */
    static const ObjRef none_type_obj;

    /* Throws, as there is no None() method */
    ObjRef operator()(std::vector<ObjRef> args) const final;

private:
    NoneType(): TypeObj {"NoneType", getMetatypeObject()} {}
};

/**
 * Underlying C++ type for the object None.
*/
class NoneObject : public Object
{
public:
    /* Singleton representing None. */
    const static ObjRef none_obj;

private:
    NoneObject() : Object {NoneType::none_type_obj} {}
};

#endif