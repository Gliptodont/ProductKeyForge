#include "ProductKeyGenerator.h"

namespace PKF
{
    ProductKeyGenerator::ProductKeyGenerator()
    {
        m_keyFormat = std::make_shared<KeyFormat>();

        m_randomGenerator = std::make_shared<MTRandomGenerator>();
        m_randomGenerator.load()->init();
    }

    std::optional<std::string> ProductKeyGenerator::generateKey() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        const auto keyFormat = m_keyFormat.load();

        if (keyFormat->validate() == false)
        {
            return std::nullopt;
        }

        std::string key;

        size_t segmentCount = keyFormat->getSegmentCount();
        size_t segmentLength = keyFormat->getSegmentLength();
        char separator = keyFormat->getSeparator();

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

        if (keyFormat->getHasChecksum())
        {
            auto checksumAlgorithm = m_checksumAlgorithm.load();

            if (checksumAlgorithm == nullptr)
            {
                std::cerr << "Warning: RandomGenerator is null, setting to default." << std::endl;
                m_checksumAlgorithm.store(std::make_shared<BaseChecksumAlgorithm>());
                checksumAlgorithm = m_checksumAlgorithm.load();
            }

            int checksum = checksumAlgorithm->calculate(key, keyFormat->getSeparator());

            key.push_back(keyFormat->getSeparator());
            key.append(std::to_string(checksum));
        }

        return key;
    }

    std::optional<std::string> ProductKeyGenerator::generateSegment(size_t length) const
    {
        std::string segment;
        segment.reserve(length);

        auto randomGenerator = m_randomGenerator.load();
        auto keyFormat = m_keyFormat.load();

        for (size_t i = 0; i < length; ++i)
        {
            auto randomCharacter = randomGenerator->getRandomCharacter(keyFormat->getCharacters());

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

        auto view = key | std::views::split(m_keyFormat.load()->getSeparator());

        for (auto&& part : view)
        {
            segments.emplace_back(std::string_view{ part.begin(), part.end() });
        }

        return segments;
    }

    std::shared_ptr<KeyFormat> ProductKeyGenerator::getKeyFormat() const
    {
        return m_keyFormat.load();
    }

    bool ProductKeyGenerator::setKeyFormat(const std::shared_ptr<KeyFormat>& newKeyFormat)
    {
        if (newKeyFormat == nullptr)
        {
            std::cerr << "Warning: Failed to set KeyFormat because it is null." << std::endl;
            return false;
        }

        m_keyFormat.store(newKeyFormat);
        return true;
    }

    std::shared_ptr<IRandomGenerator> ProductKeyGenerator::getRandomGenerator() const
    {
        return m_randomGenerator.load();
    }

    bool ProductKeyGenerator::setRandomGenerator(const std::shared_ptr<IRandomGenerator>& newRandomGenerator)
    {
        if (newRandomGenerator == nullptr)
        {
            std::cerr << "Warning: Failed to set RandomGenerator because it is null." << std::endl;
            return false;
        }

        m_randomGenerator.store(newRandomGenerator);
        return true;
    }

    std::shared_ptr<IChecksumAlgorithm> ProductKeyGenerator::getChecksumAlgorithm() const
    {
        return m_checksumAlgorithm.load();
    }

    bool ProductKeyGenerator::setChecksumAlgorithm(const std::shared_ptr<IChecksumAlgorithm>& newChecksumAlgorithm)
    {
        if (newChecksumAlgorithm == nullptr)
        {
            std::cerr << "Warning: Failed to set ChecksumAlgorithm because it is null." << std::endl;
            return false;
        }

        m_checksumAlgorithm.store(newChecksumAlgorithm);
        return true;
    }
} // namespace PKF