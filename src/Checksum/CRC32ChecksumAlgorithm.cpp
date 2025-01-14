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