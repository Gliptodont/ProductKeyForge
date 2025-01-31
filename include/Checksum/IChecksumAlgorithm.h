#pragma once

#include <string>

#include "KeyFormat.h"

namespace PKF
{
    class IChecksumAlgorithm
    {
    public:
        virtual ~IChecksumAlgorithm() = default;

        [[nodiscard]] virtual int calculate(const std::string& key, char separator) const = 0;
        [[nodiscard]] virtual bool validate(const std::string& key, char separator) const = 0;

        [[nodiscard]] bool validate(const std::string& key, int checksum, char separator) const
        {
            if (key.empty())
            {
                std::cerr << "Error: Empty key." << std::endl;
                return false;
            }

            if (separator == '\0')
            {
                std::cerr << "Error: Empty separator character." << std::endl;
                return false;
            }

            std::string fullKey = key + separator + std::to_string(checksum);

            return validate(fullKey, separator);
        }
    };
} // namespace PKF