#include "object.hpp"

ObjRef::ObjRef(Object *obj_ptr) : _obj_ptr{obj_ptr},
                                  _ref_count{new int{0}} {}

ObjRef::ObjRef(const ObjRef &ref)
    : _obj_ptr{ref._obj_ptr},
    _ref_count{ref._ref_count} {
    (*_ref_count)++;
}

ObjRef::ObjRef(ObjRef &&ref) noexcept: _obj_ptr{ref._obj_ptr},
                               _ref_count{ref._ref_count} {}

ObjRef &ObjRef::operator=(const ObjRef& ref) {
    // Handle self assignment
    if (this == &ref) {
        return *this;
    }

    _obj_ptr = ref._obj_ptr;
    _ref_count = ref._ref_count;
    (*_ref_count)++;
    return *this;
}

ObjRef &ObjRef::operator=(ObjRef &&ref) noexcept {
    _obj_ptr = ref._obj_ptr;
    _ref_count = ref._ref_count;
    return *this;
}

Object& ObjRef::operator*() const {
    return *_obj_ptr;
}

Object* ObjRef::operator->() const {
    return _obj_ptr;
}

bool ObjRef::operator==(const ObjRef &rhs) const {
    return _obj_ptr == rhs._obj_ptr;
}

Object *ObjRef::getPtr() const {
    return _obj_ptr;
}

ObjRef::~ObjRef() {
    (*_ref_count)--;

    if (*_ref_count == 0) {
        delete _ref_count;
        delete _obj_ptr;
    }
}

void Object::setAttribute([[maybe_unused]] std::string attr, [[maybe_unused]] ObjRef ref) {
    throw std::runtime_error{"Not supported"};
}

ObjRef Object::getAttribute([[maybe_unused]] std::string attr) const {
    throw std::runtime_error{"Not supported"};
}

ObjRef getNullObjRef() {
    static ObjRef null_obj_ref = ObjRef{};
    return null_obj_ref;
}