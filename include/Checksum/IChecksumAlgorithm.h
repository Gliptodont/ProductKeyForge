#pragma once

#include <string>

#include "KeyFormat.h"

namespace PKF
{
    class IChecksumAlgorithm
    {
    public:
        virtual ~IChecksumAlgorithm() = default;

        virtual int calculate(const std::string&, char) const = 0;
        virtual bool validate(const std::string&, char) const = 0;

        [[nodiscard]] bool validate(const std::string& key, int checksum, char separator) const
        {
            std::string fullKey = key + separator + std::to_string(checksum);

            return validate(fullKey, separator);
        }
    };
} // namespace PKF