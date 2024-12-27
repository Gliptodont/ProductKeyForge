#include "ProductKeyGenerator.h"

namespace PKF
{
    std::optional<std::string> ProductKeyGenerator::generateKey() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_keyFormat->validate() == false)
        {
            return std::nullopt;
        }

        return "h";
    }

    std::optional<std::vector<std::string>>  ProductKeyGenerator::generateKeyBySegments() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_keyFormat->validate() == false)
        {
            return std::nullopt;
        }

        std::vector<std::string> result = { "h" };
        return result;
    }

    std::string ProductKeyGenerator::generateSegment(size_t length) const
    {
        std::string segment;
        segment.reserve(length);

        for (size_t i = 0; i < length; ++i)
        {
        }
    }

    bool ProductKeyGenerator::setKeyFormat(const std::shared_ptr<KeyFormat>& newKeyFormat)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (newKeyFormat == nullptr)
        {
            std::cerr << "Error: Failed to set KeyFormat because it is null." << std::endl;
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
            std::cerr << "Error: Failed to set RandomGenerator because it is null." << std::endl;
            return false;
        }

        m_randomGenerator = newRandomGenerator;
        return true;
    }
} // namespace PKF