#pragma once

#include <ctime>
#include <iostream>
#include <mutex>

#include "IRandomGenerator.h"

#include <cstdint>

namespace PKF
{
    class XorshiftGenerator final : public IRandomGenerator
    {
    public:
        void init() override;
        void initWithSeed(uint32_t seed);
        std::optional<char> getRandomCharacter(const std::string& characters) override;

    private:
        std::mutex m_mutex;
        uint32_t m_state = 1;
    };
}