#include <vector>
#include "type.hpp"
#include "object.hpp"

#ifndef BUILTIN_TYPES_STRING_HPP_
#   define BUILTIN_TYPES_STRING_HPP_

class StringType: public TypeObj {
public:
    const static ObjRef string_type_obj;

    ObjRef operator()(std::vector<ObjRef> args) const override;

    ~StringType() = default;

private:
    StringType(): TypeObj {"str", getMetatypeObject()} {}
};

class StringObj : public Object
{
public:
    StringObj(const std::string &str);

    StringObj(std::string &&str);

    const std::string &getValue() const { return _value; }

private:
    std::string _value;
};

#endif