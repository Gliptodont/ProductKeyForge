#pragma once

#include <cctype>
#include <iostream>

#include "Encryption/IEncryptionAlgorithm.h"

namespace PKF
{
    class VigenereCipher final : public IEncryptionAlgorithm
    {
    public:
        [[nodiscard]] std::optional<std::string> encrypt(const std::string& data, const std::string& key) const override;
        [[nodiscard]] std::optional<std::string> decrypt(const std::string& encryptedData, const std::string& key) const override;

    private:
        [[nodiscard]] char shiftChar(char ch, int shift, bool encrypt) const;
    };
} // namespace PKF
