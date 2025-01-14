#include "RandomGenerator/MTRandomGenerator.h"


namespace PKF
{
    void MTRandomGenerator::init()
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        m_rng32.seed(std::random_device{}());
    }

    std::optional<char> MTRandomGenerator::getRandomCharacter(const std::string& characters)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (characters.empty())
        {
            std::cerr << "Error: Characters string is empty!" << std::endl;
            return std::nullopt;
        }

        std::uniform_int_distribution<size_t> dist(0, characters.size() - 1);
        const size_t index = dist(m_rng32);

        return characters[index];
    }
} // namespace PKF
