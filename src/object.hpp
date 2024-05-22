#include <string>

#ifndef OBJECT_HPP_
#   define OBJECT_HPP_

class Object;

class ObjRef {
public:
    ObjRef(Object *obj_ptr);

    ObjRef(const ObjRef &ref);

    ObjRef &operator=(const ObjRef &ref);

    /* Can mark move operations as no except as there is no allocation */
    ObjRef(ObjRef &&ref) noexcept;

    ObjRef &operator=(ObjRef &&ref) noexcept;

    /* Allows uses as a normal pointer */
    Object &operator*() const;

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

    virtual ObjRef getAttribute(std::string attr) const;

    /* Required virtual destructors for virtual base classes */
    virtual ~Object() = default;

private:
    ObjRef _type;
};

#endif