#include "gtest/gtest.h"
#include "ProductKeyGenerator.h"
#include "KeyFormat.h"
#include "RandomGenerator/XorshiftGenerator.h"
#include "Checksum/CRC32ChecksumAlgorithm.h"

class ProductKeyGeneratorTest : public ::testing::Test {
protected:
    void SetUp() override {
        keyFormat = std::make_shared<PKF::KeyFormat>();
        keyFormat->setSegmentCount(4);
        keyFormat->setSegmentLength(5);
        keyFormat->setSeparator('-');
        keyFormat->setHasChecksum(true);

        randomGenerator = std::make_shared<PKF::XorshiftGenerator>();
        randomGenerator->init();

        checksumAlgorithm = std::make_shared<PKF::CRC32ChecksumAlgorithm>();

        productKeyGenerator = std::make_unique<PKF::ProductKeyGenerator>(keyFormat, randomGenerator);
        productKeyGenerator->setChecksumAlgorithm(checksumAlgorithm);
    }

    std::shared_ptr<PKF::KeyFormat> keyFormat;
    std::shared_ptr<PKF::IRandomGenerator> randomGenerator;
    std::shared_ptr<PKF::IChecksumAlgorithm> checksumAlgorithm;
    std::unique_ptr<PKF::ProductKeyGenerator> productKeyGenerator;
};

TEST_F(ProductKeyGeneratorTest, GenerateKey) {
    auto key = productKeyGenerator->generateKey();
    ASSERT_TRUE(key.has_value());
    EXPECT_EQ(key->length(), 4 * 5 + 3 + 1 + 9); // 4 segments of 5 chars, 3 separators, 1 separator for checksum, 9 digits checksum
}

TEST_F(ProductKeyGeneratorTest, ValidateKey) {
    auto key = productKeyGenerator->generateKey();
    ASSERT_TRUE(key.has_value());
    EXPECT_TRUE(checksumAlgorithm->validate(key.value(), keyFormat->getSeparator()));
}