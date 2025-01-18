#include "PKF.h"
#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"

namespace PKF
{
    class VigenereCipherTest : public ::testing::Test
    {
    protected:
        VigenereCipher cipher;
    };

    TEST_F(VigenereCipherTest, EncryptEmptyData)
    {
        auto result = cipher.encrypt("", "key");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(VigenereCipherTest, EncryptEmptyKey)
    {
        auto result = cipher.encrypt("data", "");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(VigenereCipherTest, EncryptValidData)
    {
        auto result = cipher.encrypt("HELLO", "KEY");
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), "RIJVS");
    }

    TEST_F(VigenereCipherTest, DecryptEmptyData)
    {
        auto result = cipher.decrypt("", "key");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(VigenereCipherTest, DecryptEmptyKey)
    {
        auto result = cipher.decrypt("data", "");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(VigenereCipherTest, DecryptValidData)
    {
        auto result = cipher.decrypt("RIJVS", "KEY");
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), "HELLO");
    }
} // namespace PKF