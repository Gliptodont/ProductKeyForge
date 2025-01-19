#include "Checksum/BaseChecksumAlgorithm.h"
#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"

namespace PKF
{
    class BaseChecksumAlgorithmTest : public ::testing::Test
    {
    protected:
        BaseChecksumAlgorithm checksumAlgorithm;
    };

    TEST_F(BaseChecksumAlgorithmTest, Calculate_EmptyKey_ReturnsZero)
    {
        EXPECT_EQ(checksumAlgorithm.calculate("", '-'), 0);
    }

    TEST_F(BaseChecksumAlgorithmTest, Calculate_EmptySeparator_ReturnsZero)
    {
        EXPECT_EQ(checksumAlgorithm.calculate("test-key", '\0'), 0);
    }

    TEST_F(BaseChecksumAlgorithmTest, Calculate_ValidKey_ReturnsCorrectChecksum)
    {
        EXPECT_EQ(checksumAlgorithm.calculate("test-key", '-'), 7);
    }

    TEST_F(BaseChecksumAlgorithmTest, Validate_EmptyKey_ReturnsFalse)
    {
        EXPECT_FALSE(checksumAlgorithm.validate("", '-'));
    }

    TEST_F(BaseChecksumAlgorithmTest, Validate_EmptySeparator_ReturnsFalse)
    {
        EXPECT_FALSE(checksumAlgorithm.validate("test-key-7", '\0'));
    }

    TEST_F(BaseChecksumAlgorithmTest, Validate_InvalidChecksum_ReturnsFalse)
    {
        EXPECT_FALSE(checksumAlgorithm.validate("test-key-9", '-'));
    }

    TEST_F(BaseChecksumAlgorithmTest, Validate_ValidChecksum_ReturnsTrue)
    {
        EXPECT_TRUE(checksumAlgorithm.validate("test-key-7", '-'));
    }

    TEST_F(BaseChecksumAlgorithmTest, Validate_InvalidChecksumFormat_ReturnsFalse)
    {
        EXPECT_FALSE(checksumAlgorithm.validate("test-key-abc", '-'));
    }
}