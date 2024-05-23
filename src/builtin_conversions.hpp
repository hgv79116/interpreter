#include "object.hpp"

#ifndef CONVERSIONS_HPP_
#define     CONVERSIONS_HPP_

/* Underfined behaviour of the object is not of the type required.
User of these function must verify the types before using them. */

// To int

ObjRef stringToInt(ObjRef obj);

ObjRef boolToInt(ObjRef obj);

ObjRef floatToInt(ObjRef obj);

// To float

ObjRef stringToFloat(ObjRef obj);

ObjRef boolToFloat(ObjRef obj);

ObjRef intToFloat(ObjRef obj);

// To bool

ObjRef stringToBool(ObjRef obj);

ObjRef intToBool(ObjRef obj);

ObjRef floatToBool(ObjRef obj);

// To string

ObjRef boolToString(ObjRef obj);

ObjRef intToString(ObjRef obj);

ObjRef floatToString(ObjRef obj);

#endif