#include "RandomGenerator/XorshiftGenerator.h"

namespace PKF
{
    void XorshiftGenerator::init()
    {
        std::lock_guard<std::mutex> lock(m_mutex);

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

        std::lock_guard<std::mutex> lock(m_mutex);

        m_state = seed;
    }

    std::optional<char> XorshiftGenerator::getRandomCharacter(const std::string& characters)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

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