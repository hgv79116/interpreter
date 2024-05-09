#include <string>
#include <stdexcept>
#include <unordered_map>

#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

/**
 * Simple interpreter
 * - Garbage collection with reference counting
*/

/*
    How can I abstract away garbage collection?
*/

/*
    Expression rules
    1. Variable name:
        var
    2. Unary operation:
        op expr
        where op is one of {-, +}
    3. Binary operation:
        expr op expr
        where op is one of {+, -, *, /, //}
    4. Parenthesis:
        (expr)

    Expression parsing algorithm
    A. Our first alternative is the rule-matching based algorithm
    1. Detect any non-valid characters. A character is non-valid if it is
        - Not a ()
        - Not one of of +, -, *, /, //
        - Not a valid character for naming (alphanumeric and _)
        - Not space

    2. Remove all spaces
    3. Match with the first rule:
        Check if there is no op characters, no parenthesis
    4. If does not match, match with the second rule:
        Check if the first character is an element of the unary set
        and there is no same-level operator in the rest of the expression
    5. match with the third and fourth rule.
        We have a few options here:
        + check the fourth rule, and force the rest into the third rule
        + check the third rule, and fource the rest into the fourth rule
        + check the two rules independently, and raise an error if no rules are matched
        The third option scales well if we want to add more rules in the future

    The problem is that the 4th step is quite hard to implement.

    B. We have an alternative for this rule-matching based parser:
    follow the operator precedence:
    1. First remove all spaces
    2. Find the highest precedence sub-expression wrapped by parenthesis. Replace this sub-expression
    (parenthesis inclusive) with its value. Do this until there is no parenthesis left. The expression
    can be faulty (parenthesis not matching).
    - Within the process we might need to evaluate sub-expression with no parenthesis, or the final expression
    with no-parenthesis. In any case, we recurse to evaluate these expressions with no parenthesis
    3. Within a non-parenthesized expression, we look for the operator with the highest precedence,
    find the left and right boundary of the components, and replace these with the value.

    This is not the most performant algorithm, but quite systematic.


*/

class Interpreter {
public:
    void processLine(std::string line) {
        _line_counter++;

        _trim_end(line);

        // Prefer empty() over size() == 0 as some containers (including std::list)
        // implement size() in O(n)
        if (line.empty()) {
            return;
        }

        if (_count_ident(line) != 0) {
            throw std::runtime_error
                {"Wrong identation at line " + std::to_string(_line_counter)};
        }

        if (line.find('=') != std::string::npos) {
            _process_assignment(std::move(line));
        }
        else if (line.find("print") == 0) {
            _process_print_statement(std::move(line));
        }
        else {
            throw std::runtime_error
                {"Unrecognized type of statment at line " + std::to_string(_line_counter)};
        }
    }
private:
    int _line_counter = 0;
    std::unordered_map<std::string, int> _var_map;

    void _trim_end(std::string& line) {
        while (std::isspace(line.back())) {
            line.pop_back();
        }
    }

    void _trim_start(std::string& line) {
        auto it = begin(line);
        while (it != end(line) && std::isspace(*it)) {
            ++it;
        }

        line.erase(begin(line), it);
    }

    int _count_ident(const std::string& line) {
        auto it = begin(line);
        while (it != end(line) && std::isspace(*it)) {
            ++it;
        }
        return it - begin(line);
    }

    void _trim(std::string& line) {
        _trim_end(line);
        _trim_start(line);
    }

    void _process_assignment(std::string line) {
        int equal_sign_pos = line.find('=');
        std::string lhs = line.substr(0, equal_sign_pos);
        std::string rhs = line.substr(equal_sign_pos + 1);

        _trim(lhs);
        std::string &var_name = lhs;

        // _assign(var_name, _evaluate(rhs));
    }

    void _process_print_statement(std::string line) {

    };
};

#endif