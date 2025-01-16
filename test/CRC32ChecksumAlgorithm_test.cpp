#include <gtest/gtest.h>
#include "Checksum/CRC32ChecksumAlgorithm.h"

namespace PKF
{
    class CRC32ChecksumAlgorithmTest : public ::testing::Test
    {
    protected:
        CRC32ChecksumAlgorithm algorithm;
    };

    TEST_F(CRC32ChecksumAlgorithmTest, Calculate_EmptyKey_ReturnsZero)
    {
        EXPECT_EQ(algorithm.calculate("", '-'), 0);
    }

    TEST_F(CRC32ChecksumAlgorithmTest, Calculate_EmptySeparator_ReturnsZero)
    {
        EXPECT_EQ(algorithm.calculate("test-key", '\0'), 0);
    }

    TEST_F(CRC32ChecksumAlgorithmTest, Calculate_ValidKey_ReturnsExpectedChecksum)
    {
        EXPECT_EQ(algorithm.calculate("test-key", '-'), 69288640);
    }

    TEST_F(CRC32ChecksumAlgorithmTest, Validate_EmptyKey_ReturnsFalse)
    {
        EXPECT_FALSE(algorithm.validate("", '-'));
    }

    TEST_F(CRC32ChecksumAlgorithmTest, Validate_EmptySeparator_ReturnsFalse)
    {
        EXPECT_FALSE(algorithm.validate("test-key-123456789", '\0'));
    }

    TEST_F(CRC32ChecksumAlgorithmTest, Validate_InvalidChecksum_ReturnsFalse)
    {
        EXPECT_FALSE(algorithm.validate("test-key-987654321", '-'));
    }

    TEST_F(CRC32ChecksumAlgorithmTest, Validate_ValidChecksum_ReturnsTrue)
    {
        EXPECT_TRUE(algorithm.validate("test-key-69288640", '-'));
    }
} // namespace PKF