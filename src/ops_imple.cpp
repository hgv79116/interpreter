#include <string>
#include <utility>
#include "object.hpp"
#include "callable.hpp"
#include "builtin_types/bool.hpp"
#include "ops_imple.hpp"

/* Returns the attribute if exists, returns nullptr otherwise. Undefined behaviour
if the attribute exists but is not a callable. */
Callable* getMethodIfExists(ObjRef obj, const std::string& method_name) {
    auto search_res = obj->getAttribute(method_name);

    if (!search_res) {
        return nullptr;
    }

    return dynamic_cast<Callable *>(search_res.getPtr());
}

/* Helper function for binary operators. Returns null ObjRef if no methods match */
ObjRef performOp(ObjRef lhs, ObjRef rhs, const std::string& lhs_method, const std::string& rhs_method) {
    {
        auto *callable_ptr = getMethodIfExists(lhs, lhs_method);
        if (callable_ptr != nullptr) {
            return callable_ptr->call({std::move(lhs), std::move(rhs)});
        }
    }

    {
        auto *callable_ptr = getMethodIfExists(rhs, rhs_method);
        if (callable_ptr != nullptr) {
            return callable_ptr->call({std::move(rhs), std::move(lhs)});
        }
    }

    return getNullObjRef();
}

/* Helper function for unary operators. Returns null ObjRef if the method does
not match */
ObjRef performOp(ObjRef obj, const std::string& method) {
    auto *callable_ptr = getMethodIfExists(obj, method);
    if (callable_ptr != nullptr) {
        return callable_ptr->call({std::move(obj)});
    }

    return getNullObjRef();
}

ObjRef performAdd(ObjRef lhs, ObjRef rhs) {
    static const std::string lhs_method = "__add__";
    static const std::string rhs_method = "__radd__";

    auto custom_res = performOp(lhs, rhs, lhs_method, rhs_method);

    if (custom_res) {
        return custom_res;
    }

    throw std::runtime_error{"Operation not supported"};
}

ObjRef performSub(ObjRef lhs, ObjRef rhs) {
    static const std::string lhs_method = "__sub__";
    static const std::string rhs_method = "__rsub__";

    auto custom_res = performOp(lhs, rhs, lhs_method, rhs_method);

    if (custom_res) {
        return custom_res;
    }

    throw std::runtime_error{"Operation not supported"};
}

ObjRef performMul(ObjRef lhs, ObjRef rhs) {
    static const std::string lhs_method = "__mul__";
    static const std::string rhs_method = "__rmul__";

    auto custom_res = performOp(lhs, rhs, lhs_method, rhs_method);

    if (custom_res) {
        return custom_res;
    }

    throw std::runtime_error{"Operation not supported"};
}

ObjRef performTrueDiv(ObjRef lhs, ObjRef rhs) {
    static const std::string lhs_method = "__truediv__";
    static const std::string rhs_method = "__rtruediv__";

    auto custom_res = performOp(lhs, rhs, lhs_method, rhs_method);

    if (custom_res) {
        return custom_res;
    }

    throw std::runtime_error{"Operation not supported"};
}

ObjRef performFloorDiv(ObjRef lhs, ObjRef rhs) {
    static const std::string lhs_method = "__floordiv__";
    static const std::string rhs_method = "__rfloordiv__";

    auto custom_res = performOp(lhs, rhs, lhs_method, rhs_method);

    if (custom_res) {
        return custom_res;
    }

    throw std::runtime_error{"Operation not supported"};
}

ObjRef performBool(ObjRef obj) {
    static const std::string method = "__bool__";

    auto custom_res = performOp(obj, method);

    if (custom_res) {
        return custom_res;
    }

    throw std::runtime_error{"Operation not supported"};
}

ObjRef performNot(ObjRef obj) {
    if (obj->getType() != BoolType::bool_type_obj) {
        obj = performBool(obj);
    }

    static const std::string method = "__not__";

    auto custom_res = performOp(obj, method);

    if (custom_res) {
        return custom_res;
    }

    throw std::runtime_error{"Operation not supported"};
}