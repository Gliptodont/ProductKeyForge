#include "Encryption/VigenereCipher.h"

namespace PKF
{
    std::optional<std::string> VigenereCipher::encrypt(const std::string& data, const std::string& key) const
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
        size_t keyIndex = 0;

        for (char& ch : result)
        {
            if (std::isalpha(ch))
            {
                int shift = std::tolower(key[keyIndex % key.size()]) - 'a';
                ch = shiftChar(ch, shift, true);
                ++keyIndex;
            }
        }

        return result;
    }

    std::optional<std::string> VigenereCipher::decrypt(const std::string& encryptedData, const std::string& key) const
    {
        if (encryptedData.empty())
        {
            std::cerr << "Error: Input data is empty. Please provide valid text to encrypt or decrypt." << std::endl;
            return std::nullopt;
        }

        if (key.empty())
        {
            std::cerr << "Error: Encryption key is empty. Please provide a valid key." << std::endl;
            return std::nullopt;
        }

        std::string result = encryptedData;
        size_t keyIndex = 0;

        for (char& ch : result)
        {
            if (std::isalpha(ch))
            {
                int shift = std::tolower(key[keyIndex % key.size()]) - 'a';
                ch = shiftChar(ch, shift, false);
                ++keyIndex;
            }
        }

        return result;
    }

    char VigenereCipher::shiftChar(char ch, int shift, bool encrypt) const
    {
        if (!std::isalpha(ch))
        {
            return ch;
        }

        char base = std::islower(ch) ? 'a' : 'A';
        shift = encrypt ? shift : -shift;

        return static_cast<char>(base + (ch - base + shift + 26) % 26);
    }
} // namespace PKF