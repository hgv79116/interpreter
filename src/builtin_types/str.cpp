#include <string>
#include "str.hpp"
#include "object.hpp"

const ObjRef StringType::string_type_obj = ObjRef{new StringType()};

ObjRef StringType::operator()([[maybe_unused]] std::vector<ObjRef> args) const {
    throw std::runtime_error{"To be implemented"};
}

StringObj::StringObj(const std::string &str)
    : Object{StringType::string_type_obj}, _value {str} {}

StringObj::StringObj(std::string&& str)
    : Object{StringType::string_type_obj}, _value {std::move(str)} {}