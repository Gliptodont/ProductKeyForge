#include "RandomGenerator/LinearCongruentialGenerator.h"

namespace PKF
{
    void LinearCongruentialGenerator::init()
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        m_seed = static_cast<unsigned int>(std::time(nullptr));
        m_current = m_seed;
    }

    void LinearCongruentialGenerator::initWithSeed(unsigned int seed)
    {
        if (seed == 0)
        {
            std::cerr << "Warning: Seed value is 0. Defaulting to current time." << std::endl;
            init();

            return;
        }

        std::lock_guard<std::mutex> lock(m_mutex);

        m_seed = seed;
        m_current = m_seed;
    }

    std::optional<char> LinearCongruentialGenerator::getRandomCharacter(const std::string& characters)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (characters.empty())
        {
            std::cerr << "Error: Characters string is empty!" << std::endl;
            return std::nullopt;
        }

        m_current = (multiplier * m_current + increment) % modulus;
        size_t index = m_current % characters.size();

        return characters[index];
    }
}