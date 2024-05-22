#include <string>
#include <vector>
#include <unordered_set>

#ifndef TOKENIZE_HPP_
#   define TOKENIZE_HPP_

/*
    All patterns, with priorities from low to high
    = (assignment)
    +, -, *, /, &, ^, |, ~, <, >, (single char operators)
    **, //,
    +=, -=, *=, /=, &= ^=, |=, <=, >=, !=, == (assignment combined)
    **=, //=,
    :,
    (, ), {, }, (not supported currently)
    " string ",
    ' string ',

    Ather allowed characters
    alphanumeric,
    _,
    space,
    . (member access)
*/

using PatternExtractor = std::function<bool(std::string &src, std::string &dest)>;

PatternExtractor getFixedPatternExtractor(std::string pattern) {
    int pattern_len = pattern.size();
    return [pattern, pattern_len](std::string &src, std::string &dest) -> bool
    {
        if (src.size() < pattern_len)
        {
            return false;
        }
        if (src.compare(0, pattern_len, pattern) != 0) {
            return false;
        }

        dest = pattern;
        src.erase(0, pattern_len);
        return true;
    };
}

const PatternExtractor STRING_EXTRACTOR = [](std::string &src, std::string &dest) -> bool
{
    if (src.empty())
    {
        return false;
    }

    char first_char = src[0];
    if (first_char != '\"' && first_char != '\'')
    {
        return false;
    }

    int closing_quote_pos = src.find(first_char, 1);
    if (closing_quote_pos == std::string::npos)
    {
        return false;
    }

    int string_len = closing_quote_pos + 1;
    dest = src.substr(0, string_len);
    src.erase(0, string_len);

    return true;
};

const PatternExtractor IDENTIFIER_EXTRACTOR = [](std::string &src, std::string &dest) -> bool
{
    if (src.empty())
    {
        return false;
    }
    if (src[0] != '_' && !std::isalpha(src[0]))
    {
        return false;
    }
    int len = 1;
    while (len < src.size() &&
        (src[len] == '_' || std::isalnum(src[len]))) {
        len++;
    }

    dest = src.substr(0, len);
    src.erase(0, len);
    return true;
};

const std::vector<std::string> fixed_patterns_desc_priority{
    "(", ")", ":",
    // assignment combined operators
    "**=", "//=",
    "+=", "-=", "*=", "/=", "&=", "^=", "|=", "<=", ">=", "==", "!=",
    // double character ops
    "**", "//",
    // single character operators
    "+", "-", "*", "/", "&", "^", "|", "~", "<", ">",
    // assignment
    "="
};

std::vector<PatternExtractor> getAllPatternExtractorsDescPriority() {
    std::vector<PatternExtractor> all;

    all.push_back(STRING_EXTRACTOR);

    for (auto fixed_pattern: fixed_patterns_desc_priority) {
        all.push_back(getFixedPatternExtractor(fixed_pattern));
    }

    all.push_back(IDENTIFIER_EXTRACTOR);

    return all;
}

const std::vector<PatternExtractor> pattern_extractors_desc_priority = getAllPatternExtractorsDescPriority();

std::vector<std::string>
tokenize(std::string expr)
{
    std::vector<std::string> tokens;
    std::string cur_token;

    while (!expr.empty()) {
        if (std::isspace(expr.front())) {
            expr.erase(begin(expr));
            continue;
        }

        bool matched_one = false;
        for (const auto& extractor: pattern_extractors_desc_priority) {
            if (extractor(expr, cur_token)) {
                matched_one = true;
                break;
            }
        }

        if (!matched_one) {
            throw std::runtime_error{"Failed to parse from here: " + expr};
        }

        tokens.push_back(cur_token);
        cur_token.clear();
    }

    return tokens;
}

#endif
