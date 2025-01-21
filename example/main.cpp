#include <iostream>
#include <PKF.h>

int main()
{
    // Create a KeyFormat object and configure it
    std::shared_ptr<PKF::KeyFormat> keyFormat = std::make_shared<PKF::KeyFormat>();
    keyFormat->setSegmentCount(4);
    keyFormat->setSegmentLength(5);
    keyFormat->setSeparator('-');
    keyFormat->setHasChecksum(true);

    // Create and initialize a random generator
    std::shared_ptr<PKF::IRandomGenerator> randomGenerator = std::make_shared<PKF::MTRandomGenerator>();
    randomGenerator->init();

    // Create a checksum algorithm
    std::shared_ptr<PKF::IChecksumAlgorithm> checksumAlg = std::make_shared<PKF::CRC32ChecksumAlgorithm>();

    // Create a ProductKeyGenerator with the configured KeyFormat and random generator
    PKF::ProductKeyGenerator productKeyGenerator = PKF::ProductKeyGenerator(keyFormat, randomGenerator);
    productKeyGenerator.setChecksumAlgorithm(checksumAlg);

    // Generate a product key
    auto productKey = productKeyGenerator.generateKey();

    if (productKey.has_value())
    {
        std::cout << "Product Key: " << productKey.value() << std::endl;

        // Create an encryption algorithm (ShiftCipher)
        std::shared_ptr<PKF::ShiftCipher> encryption = std::make_shared<PKF::ShiftCipher>();

        std::string key = "KEY";
        auto encryptProductKey = encryption->encrypt(productKey.value(), key);

        if (encryptProductKey.has_value())
        {
            std::cout << "Encrypt Product Key: " << encryptProductKey.value() << std::endl;
            std::cout << "Decrypt Product Key: " << encryption->decrypt(encryptProductKey.value(), key).value() << std::endl;
        }
    }

    std::cout << "------------------------------------------" << std::endl;

    // Generate a product key with additional data
    std::vector<std::string> data = {"HELLO", "WORLD"};
    auto dataProductKey = productKeyGenerator.generateKey(data, "KEY", true);

    if (dataProductKey.has_value())
    {
        std::cout << "Product Key: " << dataProductKey.value() << std::endl;

        // Create an encryption algorithm (ShiftCipher)
        std::shared_ptr<PKF::ShiftCipher> encryption = std::make_shared<PKF::ShiftCipher>();

        std::string key = "KEY";

        std::cout << "Decrypt Product Key: " << encryption->decrypt(dataProductKey.value(), key).value() << std::endl;
    }

    return 0;
}