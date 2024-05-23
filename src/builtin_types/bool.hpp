#include <vector>
#include "type.hpp"
#include "object.hpp"

/**
 * Underlying C++ type for class 'bool'.
*/
class BoolType: TypeObj {
public:
    /* Singleton representing 'bool' type. Result of type(True). */
    static const ObjRef bool_type_obj;

    /* Underlying C++ implementation for bool(). */
    ObjRef operator()(std::vector<ObjRef> args) const final;

private:
    BoolType(): TypeObj {"bool", getMetatypeObject()} {}
};

/**
 * Underlying C++ type for all objects of type bool.
*/
class BoolObject : public Object
{
public:
    /* Represents True. */
    const static ObjRef true_obj;

    /* Represents False. */
    const static ObjRef false_obj;

    /* Returns true_obj if true, returns false_obj otherwise. */
    static ObjRef getBoolObject(bool value);

    /* Returns C++ value of the bool object. */
    bool getValue() const { return _value; }

private:
    bool _value;

    BoolObject(bool value) : Object {BoolType::bool_type_obj}, _value{value} {}
};

/* Underlying C++ implementation for equal comparison between two bool objects.
 Throws if at least one object is not bool. */
ObjRef boolEqual(ObjRef lhs, ObjRef rhs);