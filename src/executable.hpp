#ifndef EXECUTABLE_HPP_
#define     EXECUTABLE_HPP_

/**
 * Base class for all executables
*/
class Executable {
public:
    Executable(const Executable &) = delete;

    Executable(Executable &&) = delete;

    Executable& operator=(const Executable &) = delete;

    Executable& operator=(Executable &&) = delete;

    virtual void execute() = 0;

    /* Required virtual destructor as executables will be hold by pointers */
    virtual ~Executable() = 0;
};

#endif