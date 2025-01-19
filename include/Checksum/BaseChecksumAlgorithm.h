#pragma once

#include "IChecksumAlgorithm.h"

namespace PKF
{
    class BaseChecksumAlgorithm final : public IChecksumAlgorithm
    {
    public:
        [[nodiscard]] int calculate(const std::string& key, char separator) const override;
        [[nodiscard]] bool validate(const std::string& key, char separator) const override;
    };
} // namespace PKF
