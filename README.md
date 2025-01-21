# ProductKeyForge

ProductKeyForge is a lightweight, cross-platform C++20 library designed to generate, validate, and even encrypt custom product keys. Built with flexibility in mind, ProductKeyForge allows you to tweak every aspect of your license keys-segment lengths, number of segments, allowed characters, checksum policies, and optional encryption-making it perfect for a wide range of licensing systems or any scenario where you need robust, customizable key generation.

---

## Table of Contents

- [Features](#features)
- [Installation](#installation)
  - [Git Clone](#git-clone)
  - [Git Submodule](#git-submodule)
- [Usage](#usage)
  - [PKF Header](#pkf-header)
  - [KeyFormat Class](#keyformat-class)
  - [ProductKeyGenerator Class](#productkeygenerator-class)
  - [Random Generators](#random-generators)
  - [Checksum Algorithms](#checksum-algorithms)
  - [Encryption Algorithms](#encryption-algorithms)
- [Examples](#examples)
- [Build and Dependencies](#build-and-dependencies)
- [License](#license)
- [Contact](#contact)

---

## Features

- Generate customizable product keys with flexible segment and character options.
- Validate keys with built-in checksum policies.
- Optional encryption for added security.
- Cross-platform support (Windows, Linux, macOS).
- Lightweight and easy to integrate.

---

## Installation

### Git Clone

To include the library in your project using `git clone`:

1. Clone the repository:

    ```` bash
    git clone https://github.com/Gliptodont/ProductKeyForge.git
    ````

2. Add the library to your `CMakeLists.txt`:

    ```` cmake
   add_subdirectory(ProductKeyForge EXCLUDE_FROM_ALL)
   target_link_libraries(YourProject PRIVATE ProductKeyForge)
   ````

### Git Submodule

To include the library as a submodule:

1. Add the repository as a submodule:

    ```` bash
   git submodule add https://github.com/Gliptodont/ProductKeyForge.git external/ProductKeyForge
   git submodule update --init --recursive
   ````
   
2. Add the library to your `CMakeLists.txt`:

    ```` cmake
   add_subdirectory(external/ProductKeyForge EXCLUDE_FROM_ALL)
   target_link_libraries(YourProject PRIVATE ProductKeyForge)
   ````
   
3. Ensure to initialize and update submodules when cloning your project:

    ```` bash
   git clone --recurse-submodules https://github.com/yourproject/yourrepo.git
   ````

---   

## Usage

### PKF Header

The `PKF.h` file serves as the main entry point for accessing key functionalities of the ProductKeyForge library. It includes:

- **Key Format:** Define the structure of product keys, such as segment lengths, allowed characters, and overall format.
- **Product Key Generator:** Generate product keys based on specified formats and configurations.
- **Random Generators:** Utilize different random number generation algorithms, such as:
    - Linear Congruential Generator
    - Mersenne Twister (MT)
    - Xorshift
- **Checksum Algorithms:** Validate keys with algorithms like:
    - CRC32
    - Custom checksum implementations
- **Encryption Algorithms:** Secure keys using:
    - Vigenere Cipher
    - XOR Encryption
    - Shift Cipher

### KeyFormat Class

The `KeyFormat` class allows you to customize the structure of your product keys. You can configure:

1. **Character Set Customization:**
    - Define the set of characters used for generating keys.
    - Ensure characters are unique and within the valid range (2–256 characters).

   ```cpp
   PKF::KeyFormat format;
   format.setCharacters("ABCD1234");
   std::string chars = format.getCharacters();
   ```

2. **Segment Length and Count:**
    - Configure the length of individual segments and the total number of segments in the key.
    - Validate that the values are within safe limits (e.g., segment length: 1–50, segment count: 1–20).

   ```cpp
   format.setSegmentLength(5);
   format.setSegmentCount(4);
   size_t length = format.getSegmentLength();
   size_t count = format.getSegmentCount();
   ```

3. **Key Separator:**
    - Specify a separator character (e.g., `-`) to distinguish between segments.
    - Ensure the separator does not conflict with the character set.

   ```cpp
   format.setSeparator('-');
   char separator = format.getSeparator();
   ```

4. **Checksum:**
    - Enable or disable the inclusion of a checksum in the key format.

   ```cpp
   format.setHasChecksum(true);
   bool hasChecksum = format.getHasChecksum();
   ```

This class provides thread-safe methods, ensuring that configurations are consistent even in concurrent environments.

### ProductKeyGenerator Class

The `ProductKeyGenerator` class handles the generation of product keys based on a specified `KeyFormat` configuration. Key features include:

1. **Basic Key Generation:**
    - Generate a product key with default or customized settings.

   ```cpp
   PKF::ProductKeyGenerator generator;
   auto key = generator.generateKey();
   if (key.has_value()) {
       std::cout << "Generated Key: " << key.value() << std::endl;
   } else {
       std::cerr << "Failed to generate key." << std::endl;
   }
   ```

2. **Custom Key Generation with Encryption:**
    - Generate a key using additional data and an encryption key.

   ```cpp
   std::vector<std::string> data = {"DATA1", "DATA2"};
   std::string encryptionKey = "MySecretKey";
   auto encryptedKey = generator.generateKey(data, encryptionKey);
   if (encryptedKey.has_value()) {
       std::cout << "Encrypted Key: " << encryptedKey.value() << std::endl;
   }
   ```

3. **Segmented Key Parsing:**
    - Split a key into its segments for easier manipulation or validation.

   ```cpp
   std::string key = "ABCD-1234-EFGH-5678";
   auto segments = generator.getKeyBySegments(key);
   for (const auto& segment : segments) {
       std::cout << "Segment: " << segment << std::endl;
   }
   ```

4. **Random Configuration:**
    - Set up a random character generator.

   ```cpp
   auto randomGenerator = std::make_shared<PKF::MTRandomGenerator>();
   randomGenerator->init();
   generator.setRandomGenerator(randomGenerator);
   ```

5. **Checksum and Encryption Configuration:**
    - Configure checksum and encryption algorithms for advanced customization.

   ```cpp
   auto checksumAlgorithm = std::make_shared<PKF::BaseChecksumAlgorithm>();
   generator.setChecksumAlgorithm(checksumAlgorithm);

   auto encryptionAlgorithm = std::make_shared<PKF::ShiftCipher>();
   generator.setEncryptionAlgorithm(encryptionAlgorithm);
   ```

### Random Generators

The library provides several random number generation algorithms to support flexible key generation:

1. **IRandomGenerator:**
    - Interface for all random generator implementations.
    - Allows you to implement custom random generation logic if needed.

   ```cpp
   class CustomRandomGenerator : public PKF::IRandomGenerator {
   public:
       void init() override {
           // Custom initialization logic
       }

       std::optional<char> getRandomCharacter(const std::string& characters) override {
           // Custom logic to pick a random character
           return characters[rand() % characters.size()];
       }
   };
   ```

2. **LinearCongruentialGenerator:**
    - A simple and fast pseudo-random number generator.

   ```cpp
   auto lcGenerator = std::make_shared<PKF::LinearCongruentialGenerator>();
   lcGenerator->init();
   generator.setRandomGenerator(lcGenerator);
   ```

3. **MTRandomGenerator:**
    - Mersenne Twister, a widely used and highly reliable random number generator.

   ```cpp
   auto mtGenerator = std::make_shared<PKF::MTRandomGenerator>();
   mtGenerator->init();
   generator.setRandomGenerator(mtGenerator);
   ```

4. **XorshiftGenerator:**
    - A lightweight and fast random number generator based on bitwise operations.

   ```cpp
   auto xorshiftGenerator = std::make_shared<PKF::XorshiftGenerator>();
   xorshiftGenerator->init();
   generator.setRandomGenerator(xorshiftGenerator);
   ```

Each generator is thread-safe and can be swapped at runtime to customize the randomization logic.

### Checksum Algorithms

The library provides the ability to compute and validate checksums using customizable algorithms. Key components include:

1. **IChecksumAlgorithm:**
    - An interface for developing custom checksum algorithms to fit specific needs.

   ```cpp
   class CustomChecksum : public PKF::IChecksumAlgorithm {
   public:
        int calculate(const std::string& key, char separator) const override {
            // Custom checksum calculation logic
            return 0;
        }
   
        bool validate(const std::string& key, char separator) const override {
            // Custom checksum validate logic
            return true;
        }
   };
   ```

2. **BaseChecksumAlgorithm:**
    - A generic base class for implementing checksum algorithms.

   ```cpp
   auto checksumAlgorithm = std::make_shared<PKF::BaseChecksumAlgorithm>();
   generator.setChecksumAlgorithm(checksumAlgorithm);
   ```

3. **CRC32ChecksumAlgorithm:**
    - Implements the CRC32 checksum algorithm for enhanced error detection.

   ```cpp
   auto crc32Algorithm = std::make_shared<PKF::CRC32ChecksumAlgorithm>();
   generator.setChecksumAlgorithm(crc32Algorithm);
   ```

### Encryption Algorithms

The library provides flexible encryption algorithms to secure your product keys. Available options include:

1. **IEncryptionAlgorithm:**
    - An interface for implementing custom encryption algorithms.

   ```cpp
   class CustomEncryption : public PKF::IEncryptionAlgorithm {
   public:
       std::optional<std::string> encrypt(const std::string& input, const std::string& key) const override {
           // Custom encryption logic
           return input + key; // Example logic
       }

       std::optional<std::string> decrypt(const std::string& input, const std::string& key) const override {
           // Custom decryption logic
           return input.substr(0, input.size() - key.size());
       }
   };
   ```

2. **ShiftCipher:**
    - A basic encryption algorithm that shifts characters by a fixed value.

   ```cpp
   auto shiftCipher = std::make_shared<PKF::ShiftCipher>();
   generator.setEncryptionAlgorithm(shiftCipher);
   ```

3. **VigenereCipher:**
    - A more advanced cipher using a repeating keyword to encode the input.

   ```cpp
   auto vigenereCipher = std::make_shared<PKF::VigenereCipher>();
   generator.setEncryptionAlgorithm(vigenereCipher);
   ```

4. **XOREncryption:**
    - A lightweight encryption algorithm using the XOR operation with a key.

   ```cpp
   auto xorEncryption = std::make_shared<PKF::XOREncryption>();
   generator.setEncryptionAlgorithm(xorEncryption);
   ```

Each algorithm can be swapped dynamically, allowing for flexible and secure key generation and validation.

---

## Examples

### Build

To build, include the flag `-DBUILD_PRODUCT_KEY_FORGE_EXAMPLE=ON`.

### Example

```` cpp
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
````

---

## Build and Dependencies

- **CMake**: Version 3.22 or higher is required.
- **C++ Standard**: C++20 is required.

### Platform-specific Requirements:

- **Linux**:
    - GCC or Clang
    - Unix Makefile

- **Windows**:
    - MSVC
    - Visual Studio 2022

- **macOS**:
    - Clang
    - Xcode

---

## License

This project is licensed under the MIT License.

---

## Contact

For any questions or issues, feel free to contact:

- **Author:** Piskarev Maksim "gliptodont"
- **Email:** gliptodont@gliptodont.ru
