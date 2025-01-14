#include "Checksum/CRC32ChecksumAlgorithm.h"

namespace PKF
{
    std::array<uint32_t, 256> CRC32ChecksumAlgorithm::generateCRCTable()
    {
        std::array<uint32_t, 256> table{};

        for (uint32_t i = 0; i < 256; ++i)
        {
            uint32_t crc = i;

            for (int j = 0; j < 8; ++j)
            {
                if (crc & 1)
                {
                    crc = (crc >> 1) ^ 0xEDB88320;
                }
                else
                {
                    crc >>= 1;
                }
            }

            table[i] = crc;
        }

        return table;
    }

    const std::array<uint32_t, 256>& CRC32ChecksumAlgorithm::getCRCTable()
    {
        static std::once_flag flag;
        static std::array<uint32_t, 256> table;

        std::call_once(flag, []()
        {
            table = generateCRCTable();
        });

        return table;
    }

    int CRC32ChecksumAlgorithm::calculate(const std::string& key, char separator) const
    {
        uint32_t crc = 0xFFFFFFFF;

        for (char ch : key)
        {
            if (ch != separator)
            {
                crc = (crc >> 8) ^ getCRCTable()[(crc ^ static_cast<unsigned char>(ch)) & 0xFF];
            }
        }

        return static_cast<int>(~crc % 1000000000);
    }

    bool CRC32ChecksumAlgorithm::validate(const std::string& key, char separator) const
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