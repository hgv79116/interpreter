#include "none.hpp"

const ObjRef NoneType::none_type_obj = ObjRef{new NoneType{}};

ObjRef NoneType::operator()([[maybe_unused]] std::vector<ObjRef> args) const {
    throw std::runtime_error{"Not supported"};
}

const ObjRef NoneObject::none_obj = ObjRef{new NoneObject{}};