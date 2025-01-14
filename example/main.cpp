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

    for (int i = 0; i < 10; i++)
    {
        // Generate a product key
        auto key = productKeyGenerator.generateKey();

        // Check if the key was generated successfully and output the result
        if (key.has_value())
        {

            std::cout << "Generated key: " << key.value() << std::endl;
            std::cout << "Checksum is valid: " << checksumAlg->validate(key.value(), keyFormat->getSeparator()) << std::endl << std::endl;
        }
        else
        {
            std::cerr << "Failed to generate key." << std::endl;
        }
    }

    std::cout << "------------------------------------------" << std::endl;

    return 0;
}