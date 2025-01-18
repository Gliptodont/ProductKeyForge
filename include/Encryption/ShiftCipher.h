#pragma once

#include <iostream>
#include <numeric>

#include "Encryption/IEncryptionAlgorithm.h"

namespace PKF
{
    class ShiftCipher final : public IEncryptionAlgorithm
    {
    public:
        [[nodiscard]] std::optional<std::string> encrypt(const std::string& data, const std::string& key) const override;
        [[nodiscard]] std::optional<std::string> decrypt(const std::string& encryptedData, const std::string& key) const override;

    private:
        static constexpr char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        static constexpr size_t charsetSize = sizeof(charset) - 1;

        [[nodiscard]] char shiftChar(char ch, int shift) const;
    };
} // namespace PKF