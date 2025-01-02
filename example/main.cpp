#include <iostream>
#include <PKF.h>

int main()
{
    // Create and configure a KeyFormat object
    auto keyFormat = std::make_shared<PKF::KeyFormat>();
    keyFormat->setSegmentCount(5);
    keyFormat->setSegmentLength(5);
    keyFormat->setSeparator('-');

    // Create and initialize a random number generator
    auto randomGenerator = std::make_shared<PKF::MTRandomGenerator>();
    randomGenerator->init();

    // Create a ProductKeyGenerator object with the specified key format and random generator
    PKF::ProductKeyGenerator productKeyGenerator = PKF::ProductKeyGenerator(keyFormat, randomGenerator);

    // Generate a product key
    auto key = productKeyGenerator.generateKey();

    // Check if the key was generated successfully and output the result
    if (key.has_value())
    {
        std::cout << "Generated key: " << key.value() << std::endl;
    }
    else
    {
        std::cerr << "Failed to generate key." << std::endl;
    }

    std::cout << "------------------------------------------" << std::endl;

    return 0;
}