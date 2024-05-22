#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#include "object.hpp"

#ifndef TYPE_HPP_
#   define TYPE_HPP_

class TypeObj: public Object {
public:
    /**
     * Constructor for a non-metaclass type object
     * Type of a type object is the type metaclass object
    */
    TypeObj(std::string name, ObjRef _metaclass) : Object{_metaclass}, _name{std::move(name)} {}

    /**
     * Method called when users call class_name()
    */
    virtual ObjRef operator()(std::vector<ObjRef> args) const = 0;

    std::string getName() const {
        return _name;
    }

private:
    std::string _name;
};

ObjRef getMetatypeObject();

#endif