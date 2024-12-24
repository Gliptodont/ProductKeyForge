#include "ProductKeyGenerator.h"

namespace PKF
{
    std::string ProductKeyGenerator::generateKey() const
    {
        return "h";
    }

    std::vector<std::string> ProductKeyGenerator::generateKeyBySegments() const
    {
        std::vector<std::string> result = { "h" };
        return result;
    }

    bool ProductKeyGenerator::setKeyFormat(const std::shared_ptr<KeyFormat>& newKeyFormat)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (newKeyFormat == nullptr)
        {
            std::cerr << "Warning: Failed to set KeyFormat because it is null." << std::endl;
            return false;
        }

        m_keyFormat = newKeyFormat;
        return true;
    }

    bool ProductKeyGenerator::setRandomGenerator(const std::shared_ptr<IRandomGenerator>& newRandomGenerator)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (newRandomGenerator == nullptr)
        {
            std::cerr << "Warning: Failed to set RandomGenerator because it is null." << std::endl;
            return false;
        }

        m_randomGenerator = newRandomGenerator;
        return true;
    }
}