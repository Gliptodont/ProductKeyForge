#include "Checksum/BaseChecksumAlgorithm.h"

namespace PKF
{
    int BaseChecksumAlgorithm::calculate(const std::string& key, const char& separator) const
    {
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

    bool BaseChecksumAlgorithm::validate(const std::string& key, const char& separator) const
    {
        size_t lastDash = key.rfind(separator);

        if (lastDash == std::string::npos)
        {
            return false;
        }

        std::string mainKey = key.substr(0, lastDash);
        int providedChecksum = std::stoi(key.substr(lastDash + 1));

        return calculate(mainKey, separator) == providedChecksum;
    }
} // namespace PKF