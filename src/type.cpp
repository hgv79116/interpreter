#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#include "object.hpp"
#include "type.hpp"
#include "builtin_types/str.hpp"

class MetaclassTypeObj: public TypeObj {
public:
    MetaclassTypeObj() : TypeObj{"type", ObjRef{this}} {};

    /**
     * Invoked when type() is called. To be implemented
    */
    ObjRef operator()([[maybe_unused]] std::vector<ObjRef> args) const override {
        throw std::runtime_error{"To be implemented"};
    }
};

/* Follows the initialise on first call to force dynamic initialisation
instead of not knowing whether the variable is initialised staticly
or dynamically */
ObjRef getMetatypeObject() {
    static ObjRef type_metaclass_obj = ObjRef{new MetaclassTypeObj()};
    return type_metaclass_obj;
}