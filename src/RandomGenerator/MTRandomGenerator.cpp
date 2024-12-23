#include "RandomGenerator/MTRandomGenerator.h"

namespace PKF
{
    void MTRandomGenerator::init()
    {
    }

    std::optional<char> MTRandomGenerator::getRandomCharacter(const std::string& characters)
    {
        if (characters.empty())
        {
            return std::nullopt;
        }
        else
        {
            return 'a';
        }
    }
} // namespace PKF
