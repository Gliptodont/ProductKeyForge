#pragma once

#include <ctime>
#include <iostream>

#include "IRandomGenerator.h"

#include <cstdint>

namespace PKF
{
    //TODO: Реализовать безопастность в потоках
    class XorshiftGenerator final : public IRandomGenerator
    {
    public:
        void init() override;
        void initWithSeed(uint32_t seed);
        std::optional<char> getRandomCharacter(const std::string& characters) override;

    private:
        uint32_t m_state = 1;
    };
}