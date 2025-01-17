#include <iostream>
#include <PKF.h>

int main()
{
    // Create and configure a KeyFormat object
    std::shared_ptr<PKF::KeyFormat> keyFormat = std::make_shared<PKF::KeyFormat>();
    keyFormat->setSegmentCount(4);
    keyFormat->setSegmentLength(5);
    keyFormat->setSeparator('-');
    keyFormat->setHasChecksum(true);

    // Create and initialize a random number generator
    std::shared_ptr<PKF::IRandomGenerator> randomGenerator = std::make_shared<PKF::XorshiftGenerator>();
    randomGenerator->init();

    std::shared_ptr<PKF::IChecksumAlgorithm> checksumAlg = std::make_shared<PKF::CRC32ChecksumAlgorithm>();

    // Create a ProductKeyGenerator object with the specified key format and random generator
    PKF::ProductKeyGenerator productKeyGenerator = PKF::ProductKeyGenerator(keyFormat, randomGenerator);
    productKeyGenerator.setChecksumAlgorithm(checksumAlg);

    auto productKey = productKeyGenerator.generateKey();

    if (productKey.has_value())
    {
        std::cout << "Product Key: " << productKey.value() << std::endl;

        std::shared_ptr<PKF::VigenereCipher> encryption = std::make_shared<PKF::VigenereCipher>();

        std::string key = "zalupa";
        auto encryptProductKey = encryption->encrypt(productKey.value(), key);

        if (encryptProductKey.has_value())
        {
            std::cout << "Encrypt Product Key: " << encryptProductKey.value() << std::endl;
            std::cout << "Decrypt Product Key: " << encryption->decrypt(encryptProductKey.value(), key).value() << std::endl;
        }
    }

    std::cout << "------------------------------------------" << std::endl;

    return 0;
}