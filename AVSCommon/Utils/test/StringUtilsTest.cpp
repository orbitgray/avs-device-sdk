/*
 * Copyright 2018-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <gtest/gtest.h>

#include <AVSCommon/Utils/String/StringUtils.h>

namespace alexaClientSDK {
namespace avsCommon {
namespace utils {
namespace test {

using namespace alexaClientSDK::avsCommon::utils::string;

/**
 * Verify that converting an empty string to an integer fails.
 */
TEST(StringUtilsTest, test_emptyStringFails) {
    int result = 0;
    ASSERT_FALSE(stringToInt("", &result));
}

/**
 * Verify that converting a simple decimal integer string to integer succeeds.
 */
TEST(StringUtilsTest, test_simpleDecimalInteger) {
    int result = 0;
    ASSERT_TRUE(stringToInt("123", &result));
    ASSERT_EQ(123, result);
}

/**
 * Verify that converting a negative decimal integer string to integer succeeds.
 */
TEST(StringUtilsTest, test_negativeInt) {
    int result = 0;
    ASSERT_TRUE(stringToInt("-987654", &result));
    ASSERT_EQ(-987654, result);
}

/**
 * Verify that converting a decimal integer string with leading whitespace to integer succeeds.
 */
TEST(StringUtilsTest, test_initialWhitespaceSucceeds) {
    int result = 0;
    ASSERT_TRUE(stringToInt("\t  10101", &result));
    ASSERT_EQ(10101, result);
}

/**
 * Verify that converting a decimal integer string with trailing whitespace to integer succeeds.
 */
TEST(StringUtilsTest, test_trailingWhitespaceSucceeds) {
    int result = 0;
    ASSERT_TRUE(stringToInt("982389\t  ", &result));
    ASSERT_EQ(982389, result);
}

/**
 * Verify that converting a decimal integer string with leading and trailing whitespace to integer succeeds.
 */
TEST(StringUtilsTest, test_leadingAndTrailingWhitespaceSucceeds) {
    int result = 0;
    ASSERT_TRUE(stringToInt("   982389   ", &result));
    ASSERT_EQ(982389, result);
}

/**
 * Verify that converting a decimal integer with leading non-whitespace and non-decimal digit characters fails.
 */
TEST(StringUtilsTest, test_nonWhitespacePrefixFails) {
    int result = 0;
    ASSERT_FALSE(stringToInt("a123", &result));
}

/**
 * Verify that converting a decimal integer with trailing non-whitespace and non-decimal digit characters fails.
 */
TEST(StringUtilsTest, test_nonWhitespaceSuffixFails) {
    int result = 0;
    ASSERT_FALSE(stringToInt("123a", &result));
}

/**
 * Verify that converting a decimal integer with leading and trailing non-whitespace and non-decimal digit
 * characters fails.
 */
TEST(StringUtilsTest, test_nonWhitespacePrefixAndSuffixFails) {
    int result = 0;
    ASSERT_FALSE(stringToInt("a123a", &result));
}

/**
 * Verify that converting a decimal integer with both leading whitespace and non-whitespace characters fails.
 */
TEST(StringUtilsTest, test_nonWhitespaceAndNonWhitespacePrefixFails) {
    int result = 0;
    ASSERT_FALSE(stringToInt("  e123", &result));
}

/**
 * Verify that converting a decimal integer with both trailing whitespace and non-whitespace characters fails.
 */
TEST(StringUtilsTest, test_nonWhitespaceAndNonWhitespaceSuffixFails) {
    int result = 0;
    ASSERT_FALSE(stringToInt("123e  ", &result));
}

/**
 * Verify that converting a decimal integer with leading and trailing whitespace and non-whitespace characters fails.
 */
TEST(StringUtilsTest, test_nonWhitespaceAndNonWhitespacePrefixAndSuffixFails) {
    int result = 0;
    ASSERT_FALSE(stringToInt("  e123e  ", &result));
}

/**
 * Verify that converting "0" to integer succeeds.
 */
TEST(StringUtilsTest, test_zeroSucceeds) {
    int result = -1;
    ASSERT_TRUE(stringToInt("0", &result));
    ASSERT_EQ(0, result);
}

/**
 * Verify that converting a floating string to integer fails.
 */
TEST(StringUtilsTest, test_decimalFloatFails) {
    int result = 0;
    ASSERT_FALSE(stringToInt("1.234", &result));
}

/**
 * Verify that converting an octal integer string si interpreted as decmal with a leading zero.
 */
TEST(StringUtilsTest, test_octalInterpretedAsDecimal) {
    int result = 0;
    ASSERT_TRUE(stringToInt("0567", &result));
    ASSERT_EQ(567, result);
}

/**
 * Verify that converting a hex integer string to integer fails.
 */
TEST(StringUtilsTest, test_hexIntFails) {
    int result = 0;
    ASSERT_FALSE(stringToInt("0x321", &result));
}

/**
 * Verify that converting a too large integer string to int fails.
 */
TEST(StringUtilsTest, test_tooLargeIntFails) {
    int result = 0;
    ASSERT_FALSE(stringToInt("987654321987654321987654321", &result));
}

/**
 * Verify that converting a too small integer string to int fails.
 */
TEST(StringUtilsTest, test_tooSmallIntFails) {
    int result = 0;
    ASSERT_FALSE(stringToInt("-11111111111111111111111111", &result));
}

/**
 * Verify that converting a string with multiple numbers in it fails.
 */
TEST(StringUtilsTest, test_multipleNumbers) {
    int result = 0;
    ASSERT_FALSE(stringToInt("123 123", &result));
    ASSERT_FALSE(stringToInt(" 123 123", &result));
    ASSERT_FALSE(stringToInt("123 123 ", &result));
    ASSERT_FALSE(stringToInt(" 123 123 ", &result));
    ASSERT_FALSE(stringToInt("1 2 3", &result));
}

/**
 * Verify that converting a empty string to lower case works.
 */
TEST(StringUtilsTest, test_toLowerEmptyString) {
    ASSERT_EQ(stringToLowerCase(""), "");
}

/**
 * Verify that converting a lower case string to lower case works.
 */
TEST(StringUtilsTest, test_toLowerCaseString) {
    ASSERT_EQ(stringToLowerCase("abc"), "abc");
}

/**
 * Verify that converting a Upper case string to lower case works.
 */
TEST(StringUtilsTest, test_toUpperCaseString) {
    ASSERT_EQ(stringToLowerCase("ABC"), "abc");
}

/**
 * Verify that converting a Camel case string to lower case works.
 */
TEST(StringUtilsTest, test_toCamelCaseString) {
    ASSERT_EQ(stringToLowerCase("AbCd"), "abcd");
}

}  // namespace test
}  // namespace utils
}  // namespace avsCommon
}  // namespace alexaClientSDK
