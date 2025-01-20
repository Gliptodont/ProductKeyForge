# ProductKeyForge

ProductKeyForge is a lightweight, cross-platform C++20 library designed to generate, validate, and even encrypt custom product keys. Built with flexibility in mind, ProductKeyForge allows you to tweak every aspect of your license keys-segment lengths, number of segments, allowed characters, checksum policies, and optional encryption-making it perfect for a wide range of licensing systems or any scenario where you need robust, customizable key generation.

---

- Author: Piskarev Maksim "gliptodont"
- Email: gliptodont@gliptodont.ru

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
   add_subdirectory(ProductKeyForge)
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
   add_subdirectory(external/ProductKeyForge)
   target_link_libraries(YourProject PRIVATE ProductKeyForge)
   ````
   
3. Ensure to initialize and update submodules when cloning your project:

    ```` bash
   git clone --recurse-submodules https://github.com/yourproject/yourrepo.git
   ````
   
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

4. **Checksum and Encryption Configuration:**
    - Configure checksum and encryption algorithms for advanced customization.

   ```cpp
   auto checksumAlgorithm = std::make_shared<PKF::BaseChecksumAlgorithm>();
   generator.setChecksumAlgorithm(checksumAlgorithm);

   auto encryptionAlgorithm = std::make_shared<PKF::ShiftCipher>();
   generator.setEncryptionAlgorithm(encryptionAlgorithm);
   ```