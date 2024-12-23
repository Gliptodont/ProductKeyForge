#pragma once

#include "IRandomGenerator.h"

namespace PKF
{
    class MTRandomGenerator final : public IRandomGenerator
    {
    public:
        void init() override;
        std::optional<char> getRandomCharacter(const std::string& characters) override;
    };
} // namespace PKF