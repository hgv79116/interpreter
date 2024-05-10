#ifndef TYPES_HPP_
#define TYPES_HPP_


/*
    In Python everything is an object
    The pool of objects is managed by the interpreter
    Variable assignment are just basically a reference to the actual object.

    1. Immutable types
    - expressions create new objects
    - assignment basically bind the identifiers to these new objects.

    2. Object creation
    - There are only two ways an object can be created or deleted:
        + By expression evaluation
        + By del statement

    Question:
        How are objects stored in Python?


*/

class List;
class Tuple;

using IntPtr = int*;
using FloatPtr = float*;
using StringPtr = std::string*;
using BooleanPtr = bool *;
using ListPtr = List *;
using TuplePtr = Tuple *;

using ObjectPtr = std::variant<IntPtr, FloatPtr, StringPtr, BooleanPtr, ListPtr, TuplePtr>;

struct Variable {
    std::string name;
    ObjectPtr ptr;
};

class List
{
};

class Tuple
{
};

#endif