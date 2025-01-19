#include "Encryption/ShiftCipher.h"

namespace PKF
{
    std::optional<std::string> ShiftCipher::encrypt(const std::string& data, const std::string& key) const
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

        int shift = std::accumulate(key.begin(), key.end(), 0) % charsetSize;

        std::string result = data;

        for (char& ch : result)
        {
            ch = shiftChar(ch, shift);
        }

        return result;
    }

    std::optional<std::string> ShiftCipher::decrypt(const std::string& encryptedData, const std::string& key) const
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

        int shift = std::accumulate(key.begin(), key.end(), 0) % charsetSize;

        std::string result = encryptedData;

        for (char& ch : result)
        {
            ch = shiftChar(ch, -shift);
        }

        return result;
    }

    char ShiftCipher::shiftChar(char ch, int shift) const
    {
        const char* pos = nullptr;

        for (const char* it = charset; it < charset + charsetSize; ++it)
        {
            if (*it == ch)
            {
                pos = it;
                break;
            }
        }

        if (pos == nullptr)
        {
            return ch;
        }

        size_t index = static_cast<size_t>(pos - std::begin(charset));
        size_t newIndex = (index + shift + charsetSize) % charsetSize;

        return charset[newIndex];
    }
} // namespace PKF