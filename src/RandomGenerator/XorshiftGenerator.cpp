#include "RandomGenerator/XorshiftGenerator.h"

namespace PKF
{
    void XorshiftGenerator::init()
    {
        m_state = static_cast<uint32_t>(std::time(nullptr));
    }

    void XorshiftGenerator::initWithSeed(uint32_t seed)
    {
        if (seed == 0)
        {
            std::cerr << "Warning: Seed value is 0. Defaulting to current time." << std::endl;
            init();

            return;
        }

        m_state = seed;
    }

    std::optional<char> XorshiftGenerator::getRandomCharacter(const std::string& characters)
    {
        if (characters.empty())
        {
            std::cerr << "Error: Characters string is empty!" << std::endl;
            return std::nullopt;
        }

        m_state ^= m_state << 13;
        m_state ^= m_state >> 17;
        m_state ^= m_state << 5;

        size_t index = m_state % characters.size();

        return characters[index];
    }
}