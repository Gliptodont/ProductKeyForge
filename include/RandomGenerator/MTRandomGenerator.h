#pragma once

#include <random>
#include <iostream>

#include "IRandomGenerator.h"

namespace PKF
{
    //TODO: Реализовать безопастность в потоках
    class MTRandomGenerator final : public IRandomGenerator
    {
    public:
        void init() override;
        std::optional<char> getRandomCharacter(const std::string& characters) override;

    private:
        std::mt19937 m_rng32;
    };
} // namespace PKF