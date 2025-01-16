#pragma once

#include <array>

#include "IChecksumAlgorithm.h"

namespace PKF
{
    class CRC32ChecksumAlgorithm final : public IChecksumAlgorithm
    {
    public:
        [[nodiscard]] int calculate(const std::string& key, char separator) const override;
        [[nodiscard]] bool validate(const std::string& key, char separator) const override;

    private:
        static std::array<uint32_t, 256> generateCRCTable();
        static const std::array<uint32_t, 256>& getCRCTable();
    };

} // namespace PKF