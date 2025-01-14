#include "ProductKeyGenerator.h"

namespace PKF
{
    ProductKeyGenerator::ProductKeyGenerator()
    {
        m_keyFormat = std::make_shared<KeyFormat>();

        m_randomGenerator = std::make_shared<MTRandomGenerator>();
        m_randomGenerator->init();
    }

    std::optional<std::string> ProductKeyGenerator::generateKey() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_keyFormat->validate() == false)
        {
            return std::nullopt;
        }

        std::string key;

        size_t segmentCount = m_keyFormat->getSegmentCount();
        size_t segmentLength = m_keyFormat->getSegmentLength();
        char separator = m_keyFormat->getSeparator();

        for (size_t i = 0; i < segmentCount; ++i)
        {
            auto segment = generateSegment(segmentLength);

            if (segment.has_value())
            {
                key.append(segment.value());

                if (i < segmentCount - 1)
                {
                    key.push_back(separator);
                }
            }
            else
            {
                return std::nullopt;
            }
        }

        if (m_keyFormat->getHasChecksum())
        {
            if (m_checksumAlgorithm == nullptr)
            {
                std::cerr << "Warning: RandomGenerator is null, setting to default." << std::endl;
                m_checksumAlgorithm = std::make_shared<BaseChecksumAlgorithm>();
            }

            int checksum = m_checksumAlgorithm->calculate(key, m_keyFormat->getSeparator());

            key.push_back(m_keyFormat->getSeparator());
            key.append(std::to_string(checksum));
        }

        return key;
    }

    std::optional<std::string> ProductKeyGenerator::generateSegment(size_t length) const
    {
        std::string segment;
        segment.reserve(length);

        for (size_t i = 0; i < length; ++i)
        {
            auto randomCharacter = m_randomGenerator->getRandomCharacter(m_keyFormat->getCharacters());

            if (randomCharacter.has_value())
            {
                segment.push_back(randomCharacter.value());
            }
            else
            {
                std::cerr << "Error: Failed to generate random character." << std::endl;
                return std::nullopt;
            }
        }

        return segment;
    }

    std::vector<std::string> ProductKeyGenerator::getKeyBySegments(std::string_view key) const
    {
        std::vector<std::string> segments;

        auto view = key | std::views::split(m_keyFormat->getSeparator());

        for (auto&& part : view)
        {
            segments.emplace_back(std::string_view{part.begin(), part.end()});
        }


        return segments;
    }

    std::shared_ptr<KeyFormat> ProductKeyGenerator::getKeyFormat() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_keyFormat;
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

    std::shared_ptr<IRandomGenerator> ProductKeyGenerator::getRandomGenerator() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_randomGenerator;
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

    std::shared_ptr<IChecksumAlgorithm> ProductKeyGenerator::getChecksumAlgorithm() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_checksumAlgorithm;
    }

    bool ProductKeyGenerator::setChecksumAlgorithm(const std::shared_ptr<IChecksumAlgorithm>& newChecksumAlgorithm)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (newChecksumAlgorithm == nullptr)
        {
            std::cerr << "Warning: Failed to set ChecksumAlgorithm because it is null." << std::endl;
            return false;
        }

        m_checksumAlgorithm = newChecksumAlgorithm;
        return true;
    }
} // namespace PKF