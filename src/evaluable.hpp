#include "object.hpp"

#ifndef EVALUABLE_HPP_
#define     EVALUABLE_HPP_

/**
 * Base class for all evaluables
*/
class Evaluable {
public:
    Evaluable(const Evaluable &) = delete;

    Evaluable(Evaluable &&) = delete;

    Evaluable &operator=(const Evaluable &) = delete;

    Evaluable &operator=(Evaluable &&) = delete;

    /* Returns the evaluated value.
    Returns None by default. */
    virtual ObjRef evaluate() = 0;

    /* Required virtual destructor as evaluables will be hold by pointers */
    virtual ~Evaluable() = 0;
};

#endif