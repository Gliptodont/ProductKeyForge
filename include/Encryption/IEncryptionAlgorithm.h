#pragma once

#include <string>
#include <optional>

namespace PKF
{
    class IEncryptionAlgorithm
    {
    public:
        virtual ~IEncryptionAlgorithm() = default;

        [[nodiscard]] virtual std::optional<std::string> encrypt(const std::string& data, const std::string& key) const = 0;
        [[nodiscard]] virtual std::optional<std::string> decrypt(const std::string& encryptedData, const std::string& key) const = 0;
    };
}