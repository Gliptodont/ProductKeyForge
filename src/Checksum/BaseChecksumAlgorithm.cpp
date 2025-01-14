#include "Checksum/BaseChecksumAlgorithm.h"

namespace PKF
{
    int BaseChecksumAlgorithm::calculate(const std::string& key, char separator) const
    {
        if (key.empty())
        {
            std::cerr << "Error: Empty key." << std::endl;
            return 0;
        }

        if (separator == '\0')
        {
            std::cerr << "Error: Empty separator character." << std::endl;
            return 0;
        }

        int sum = 0;

        for (const char ch : key)
        {
            if (ch != separator)
            {
                sum += static_cast<int>(ch);
            }
        }

        return sum % 10;
    }

    bool BaseChecksumAlgorithm::validate(const std::string& key, char separator) const
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

        size_t lastDash = key.rfind(separator);

        if (lastDash == std::string::npos)
        {
            return false;
        }

        const std::string mainKey = key.substr(0, lastDash);
        const std::string checksumPart = key.substr(lastDash + 1);

        int providedChecksum = 0;

        try
        {
            std::size_t pos;
            providedChecksum = std::stoi(checksumPart, &pos);

            if (pos != checksumPart.size())
            {
                std::cerr << "Error: Invalid checksum value." << std::endl;
                return false;
            }
        }
        catch (const std::exception&)
        {
            std::cerr << "Error: Failed to convert checksum to int." << std::endl;
            return false;
        }

        return calculate(mainKey, separator) == providedChecksum;
    }
} // namespace PKF