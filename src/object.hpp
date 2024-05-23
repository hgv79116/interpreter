#include <string>

#ifndef OBJECT_HPP_
#   define OBJECT_HPP_

class Object;

class ObjRef {
public:
    /* Default constructor. _obj_ptr is initialised to null */
    ObjRef() : _obj_ptr {nullptr}, _ref_count {new int{0}} {};

    /* Constructs an ObjRef from an Object pointer */
    ObjRef(Object *obj_ptr);

    ObjRef(const ObjRef &ref);

    ObjRef &operator=(const ObjRef &ref);

    /* Can mark move operations as no except as there is no allocation */
    ObjRef(ObjRef &&ref) noexcept;

    ObjRef &operator=(ObjRef &&ref) noexcept;

    /* Allows uses as a normal pointer */
    Object &operator*() const;

    /* Allows uses as a normal pointer */
    Object *operator->() const;

    /* Checks if the inner pointer is nullptr */
    operator bool() const { return _obj_ptr == nullptr; }

    /* Equality comparison */
    bool operator==(const ObjRef &rhs) const;

    /* Gets the inner object pointer */
    Object *getPtr() const;

    ~ObjRef();

private:
    Object *_obj_ptr;
    int *_ref_count;
};

class Object {
public:
    Object(ObjRef type): _type {std::move(type)} {}

    Object(const Object &obj) = delete;

    Object(Object &&obj) = delete;

    Object &operator=(const Object &obj) = delete;

    Object &operator=(Object &&obj) = delete;

    ObjRef getType() const;

    virtual void setAttribute(std::string attr, ObjRef ref);

    /* Gets the attribute with corresponding name. Returns null ObjRef if
    there are no such attributes. */
    virtual ObjRef getAttribute(std::string attr) const;

    /* Required virtual destructors for virtual base classes */
    virtual ~Object() = default;

private:
    ObjRef _type;
};

#endif