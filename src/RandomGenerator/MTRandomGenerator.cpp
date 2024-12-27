#include "RandomGenerator/MTRandomGenerator.h"

namespace PKF
{
    void MTRandomGenerator::init()
    {
        m_rng32.seed(std::random_device{}());
    }

    std::optional<char> MTRandomGenerator::getRandomCharacter(const std::string& characters)
    {
        if (characters.empty())
        {
            return std::nullopt;
        }

        std::uniform_int_distribution<size_t> dist(0, characters.size() - 1);
        return characters[dist(m_rng32)];
    }
} // namespace PKF
