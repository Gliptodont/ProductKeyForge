#pragma once

#include <ctime>
#include <iostream>

#include "IRandomGenerator.h"

namespace PKF
{
    //TODO: Реализовать безопастность в потоках
    class LinearCongruentialGenerator final : public IRandomGenerator
    {
    public:
        void init() override;
        void initWithSeed(unsigned int seed);
        std::optional<char> getRandomCharacter(const std::string& characters) override;

    private:
        unsigned int m_seed = 1;
        unsigned int m_current = 1;
        const unsigned int multiplier = 1664525;
        const unsigned int increment = 1013904223;
        const unsigned int modulus = 0xFFFFFFFF;
    };
}