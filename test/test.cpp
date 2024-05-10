#include <vector>
#include <string>

#include "gtest/gtest.h"
#include "tokenize.hpp"

void expect_successful_extraction(PatternExtractor extractor, std::string prefix, std::string suffix) {
    std::string src = prefix + suffix;

    // We expect that the initial value in dest should not affect the output
    // if the extraction is successful
    std::string dest = std::string(3, 'a');

    bool res = extractor(src, dest);

    EXPECT_EQ(res, true);
    EXPECT_EQ(dest, prefix);
    EXPECT_EQ(src, suffix);

}

void expect_failed_extraction (PatternExtractor extractor, std::string prefix, std::string suffix) {
    std::string src = prefix + suffix;

    // We expect that the initial value in dest should not be changed
    std::string dest = std::string(3, 'a');

    std::string saved_src = src, saved_dest = dest;

    bool res = extractor(src, dest);

    EXPECT_EQ(res, false);
    EXPECT_EQ(dest, saved_dest);
    EXPECT_EQ(src, saved_src);
}


TEST(StringExtractorTest, SingleQuote) {
    expect_successful_extraction(
        STRING_EXTRACTOR,
        "\' som kind of string \'",
        " lsjdfldsfjlskfj dslkf "
    );
}

TEST(StringExtractorTest, DoubleQuote) {
    expect_successful_extraction(
        STRING_EXTRACTOR,
        "\" som kind of string \"",
        " lsjdfldsfjlskfj dslkf "
    );
}

TEST(StringExtractorTest, NoClosingQuote) {
    expect_failed_extraction(
        STRING_EXTRACTOR,
        "\" som kind of string",
        " lsjdfldsfjlskfj dslkf "
    );
}

TEST(StringExtractorTest, MismatchedClosingQuote) {
    expect_failed_extraction(
        STRING_EXTRACTOR,
        "\" som kind of string\'",
        " lsjdfldsfjlskfj dslkf "
    );
}

TEST(StringExtractorTest, SingleQuoteInsideDoubleQuote) {
    expect_successful_extraction(
        STRING_EXTRACTOR,
        "\" som kind of \'string\"",
        " lsjdfldsfjlskfj dslkf "
    );
}

TEST(IdentifierExtractorTest, StartingDigit) {
    expect_failed_extraction(
        IDENTIFIER_EXTRACTOR,
        "9abc",
        " lsjdfldsfjlskfj dslkf "
    );
}

TEST(IdentifierExtractorTest, StartingUnderscore) {
    expect_successful_extraction(
        IDENTIFIER_EXTRACTOR,
        "_abc",
        " lsjdfldsfjlskfj dslkf "
    );
}

TEST(IdentifierExtractorTest, MidStringDigits) {
    expect_successful_extraction(
        IDENTIFIER_EXTRACTOR,
        "_ab9c",
        " lsjdfldsfjlskfj dslkf "
    );
}

TEST(FixedPatternExtractorsTest, ShouldSucceed) {
    expect_successful_extraction(
        getFixedPatternExtractor("  random pattern"),
        "  random pattern",
        " lsjdfldsfjlskfj dslkf "
    );
}

TEST(FixedPatternExtractorsTest, ShouldFail) {
    expect_failed_extraction(
        getFixedPatternExtractor("  random pattern"),
        "  random pat",
        " lsjdfldsfjlskfj dslkf "
    );
}


std::string toString(const std::vector<std::string>& tokens) {
    std::string res;
    for (auto token: tokens) {
        res.push_back(',');
        res.insert(std::end(res), std::begin(token), std::end(token));
    }
    return res;
}

TEST(TokenizationTest, SimpleLines) {
    std::string line = "a += b";
    std::vector<std::string> expected_result {"a", "+=", "b"};
    EXPECT_EQ(tokenize(line), expected_result) << "Wrong tokenization result: " << toString(tokenize(line));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}