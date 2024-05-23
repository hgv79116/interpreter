/**
 * Underlying C++ implementations for operators.
 * Currently DO NOT SUPPORT builtin types.
*/

#include <string>
#include <utility>
#include "object.hpp"

#ifndef OPS_IMPLE_HPP_
#define     OPS_IMPLE_HPP_

/* Underlying C++ implementation for the '+' operator.
Throws if the operator is not supported. */
ObjRef performAdd(ObjRef lhs, ObjRef rhs);

/* Underlying C++ implementation for the '-' operator.
Throws if the operator is not supported. */
ObjRef performSub(ObjRef lhs, ObjRef rhs);

/* Underlying C++ implementation for the '*' operator.
Throws if the operator is not supported. */
ObjRef performMul(ObjRef lhs, ObjRef rhs);

/* Underlying C++ implementation for the '/' operator.
Throws if the operator is not supported. */
ObjRef performTrueDiv(ObjRef lhs, ObjRef rhs);

/* Underlying C++ implementation for the '//' operator.
Throws if the operator is not supported. */
ObjRef performFloorDiv(ObjRef lhs, ObjRef rhs);

/* Underlying C++ implementation for the 'bool()' operator.
Throws if the operator is not supported. */
ObjRef performBool(ObjRef obj);

/* Underlying C++ implementation for the 'not' operator.
Implicitly converts to bool if the object is not a bool.
Throws if any operators are not supported. */
ObjRef performNot(ObjRef obj);

#endif