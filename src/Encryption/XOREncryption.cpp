#include "Encryption/XOREncryption.h"

namespace PKF
{
    std::optional<std::string> XOREncryption::encrypt(const std::string& data, const std::string& key) const
    {
        if (data.empty())
        {
            std::cerr << "Error: Input data is empty. Please provide valid text to encrypt or decrypt." << std::endl;
            return std::nullopt;
        }

        if (key.empty())
        {
            std::cerr << "Error: Encryption key is empty. Please provide a valid key." << std::endl;
            return std::nullopt;
        }

        std::string result = data;

        for (size_t i = 0; i < data.size(); ++i)
        {
            result[i] ^= key[i % key.size()];
        }

        return result;
    }
    std::optional<std::string> XOREncryption::decrypt(const std::string& encryptedData, const std::string& key) const
    {
        return encrypt(encryptedData, key);
    }
} // namespace PKF