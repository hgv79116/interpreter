#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#include "object.hpp"
#include "type.hpp"

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

/* Follows construct on first call idiom */
ObjRef getMetatypeObject() {
    static ObjRef type_metaclass_obj = ObjRef{new MetaclassTypeObj()};
    return type_metaclass_obj;
}