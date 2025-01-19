#include "PKF.h"
#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"

namespace PKF
{
    class XOREncryptionTest : public ::testing::Test
    {
    protected:
        XOREncryption encryption;

        std::string xorStrings(const std::string& data, const std::string& key)
        {
            std::string result = data;
            size_t keyLength = key.length();
            for (size_t i = 0; i < data.length(); ++i)
            {
                result[i] = data[i] ^ key[i % keyLength];
            }
            return result;
        }
    };

    TEST_F(XOREncryptionTest, EncryptEmptyData)
    {
        auto result = encryption.encrypt("", "key");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(XOREncryptionTest, EncryptEmptyKey)
    {
        auto result = encryption.encrypt("data", "");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(XOREncryptionTest, EncryptValidData)
    {
        auto result = encryption.encrypt("HELLO", "KEY");
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), xorStrings("HELLO", "KEY"));
    }

    TEST_F(XOREncryptionTest, DecryptEmptyData)
    {
        auto result = encryption.decrypt("", "key");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(XOREncryptionTest, DecryptEmptyKey)
    {
        auto result = encryption.decrypt("data", "");
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(XOREncryptionTest, DecryptValidData)
    {
        std::string encrypted = xorStrings("HELLO", "KEY");
        auto result = encryption.decrypt(encrypted, "KEY");
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), "HELLO");
    }
} // namespace PKF
