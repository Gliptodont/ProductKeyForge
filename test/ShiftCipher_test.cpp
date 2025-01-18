#include "PKF.h"
#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"

namespace PKF
{
    class ShiftCipherTest : public ::testing::Test
    {
    protected:
        ShiftCipher cipher;
    };

    TEST_F(ShiftCipherTest, EncryptEmptyData)
    {
        auto result = cipher.encrypt("", "key");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(ShiftCipherTest, EncryptEmptyKey)
    {
        auto result = cipher.encrypt("data", "");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(ShiftCipherTest, EncryptValidData)
    {
        auto result = cipher.encrypt("HELLO", "KEY");
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), "2z669");
    }

    TEST_F(ShiftCipherTest, DecryptEmptyData)
    {
        auto result = cipher.decrypt("", "key");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(ShiftCipherTest, DecryptEmptyKey)
    {
        auto result = cipher.decrypt("data", "");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(ShiftCipherTest, DecryptValidData)
    {
        auto result = cipher.decrypt("2z669", "KEY");
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), "HELLO");
    }
}