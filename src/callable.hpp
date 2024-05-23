#include <vector>
#include <string>
#include "executable.hpp"
#include "object.hpp"
#include "future_value.hpp"
#include "runtime.hpp"

class Callable {
public:
    Callable(Runtime *runtime, std::vector<std::string> params);

    ObjRef call(std::vector<ObjRef> args);

    void addExecutable(Executable exe);

    void setReturn(FutureValue fval);

private:
    Runtime *_runtime;
    std::vector<std::string> _params;
    std::vector<Executable> _exes;
    FutureValue _return;
};