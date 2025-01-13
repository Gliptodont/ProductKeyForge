#pragma once

#include "IChecksumAlgorithm.h"

namespace PKF
{
    //TODO: Реализовать безопастность в потоках
    class BaseChecksumAlgorithm final : public IChecksumAlgorithm
    {
    public:
        [[nodiscard]] int calculate(const std::string& key, const char& separator) const override;
        [[nodiscard]] bool validate(const std::string& key, const char& separator) const override;
    };
} // namespace PKF
