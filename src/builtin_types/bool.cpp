#include "bool.hpp"

const ObjRef BoolType::bool_type_obj = ObjRef{new BoolType{}};

ObjRef BoolType::operator()([[maybe_unused]] std::vector<ObjRef> args) const {
    throw std::runtime_error{"To be implemented"};
}

const ObjRef BoolObject::true_obj = ObjRef{new BoolObject{true}};

const ObjRef BoolObject::false_obj = ObjRef{new BoolObject{false}};

ObjRef BoolObject::getBoolObject(bool value) {
    return value ? true_obj : false_obj;
}

ObjRef boolEqual(ObjRef lhs, ObjRef rhs) {
    if (lhs->getType() != rhs->getType() ||
        lhs->getType() != BoolType::bool_type_obj) {
        throw std::runtime_error{"Wrong argument type"};
    }

    /* We can directly compare the two pointers as bool objects are singletons. */
    return BoolObject::getBoolObject(lhs.getPtr() == rhs.getPtr());
}