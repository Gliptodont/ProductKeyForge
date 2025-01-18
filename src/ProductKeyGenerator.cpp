#include "ProductKeyGenerator.h"

namespace PKF
{
    ProductKeyGenerator::ProductKeyGenerator()
    {
        m_keyFormat = std::make_shared<KeyFormat>();

        m_randomGenerator = std::make_shared<MTRandomGenerator>();
        m_randomGenerator->init();

        m_checksumAlgorithm = nullptr;
    }

    std::optional<std::string> ProductKeyGenerator::generateKey() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        std::string key;

        const auto keyFormat = m_keyFormat;

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
            generateChecksum(key);
        }

        return key;
    }

    std::optional<std::string> ProductKeyGenerator::generateKey(
        const std::vector<std::string>& data, const std::string& encryptionKey, bool isTotalNumberOfSegments) const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (data.empty())
        {
            std::cerr << "Error: data is empty." << std::endl;
            return std::nullopt;
        }

        if (encryptionKey.empty())
        {
            std::cerr << "Error: encryptionKey is empty." << std::endl;
            return std::nullopt;
        }

        size_t dataCount = data.size();

        auto encryptionAlgorithm = m_encryptionAlgorithm;

        if (encryptionAlgorithm == nullptr)
        {
            m_encryptionAlgorithm = std::make_shared<ShiftCipher>();
            encryptionAlgorithm = m_encryptionAlgorithm;
        }

        const auto keyFormat = m_keyFormat;

        size_t segmentCount = keyFormat->getSegmentCount();
        size_t segmentLength = keyFormat->getSegmentLength();
        char separator = keyFormat->getSeparator();

        std::string key;

        for (size_t i = 0; i < dataCount; ++i)
        {
            if (i == 0)
            {
                key.append(data[i]);
            }
            else
            {
                key.push_back(separator);
                key.append(data[i]);
            }
        }

        if (isTotalNumberOfSegments)
        {
            if (segmentCount > dataCount)
            {
                for (size_t i = dataCount; i < segmentCount; ++i)
                {
                    auto segment = generateSegment(segmentLength);

                    if (segment.has_value())
                    {
                        key.push_back(separator);
                        key.append(segment.value());
                    }
                    else
                    {
                        return std::nullopt;
                    }
                }
            }
        }

        if (keyFormat->getHasChecksum())
        {
            generateChecksum(key);
        }

        auto encryptKey = encryptionAlgorithm->encrypt(key, encryptionKey);

        if (encryptKey.has_value())
        {
            return encryptKey;
        }

        return std::nullopt;
    }

    std::optional<std::string> ProductKeyGenerator::generateSegment(size_t length) const
    {
        std::string segment;
        segment.reserve(length);

        auto randomGenerator = m_randomGenerator;
        auto keyFormat = m_keyFormat;

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

    void ProductKeyGenerator::generateChecksum(std::string& key) const
    {
        auto checksumAlgorithm = m_checksumAlgorithm;
        auto keyFormat = m_keyFormat;

        if (checksumAlgorithm == nullptr)
        {
            std::cerr << "Warning: RandomGenerator is null, setting to default." << std::endl;
            m_checksumAlgorithm = std::make_shared<BaseChecksumAlgorithm>();
            checksumAlgorithm = m_checksumAlgorithm;
        }

        int checksum = checksumAlgorithm->calculate(key, keyFormat->getSeparator());

        key.push_back(keyFormat->getSeparator());
        key.append(std::to_string(checksum));
    }

    std::vector<std::string> ProductKeyGenerator::getKeyBySegments(std::string_view key) const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        std::vector<std::string> segments;

        auto view = key | std::views::split(m_keyFormat->getSeparator());

        for (auto&& part : view)
        {
            segments.emplace_back(std::string_view{ part.begin(), part.end() });
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

    std::shared_ptr<IEncryptionAlgorithm> ProductKeyGenerator::getEncryptionAlgorithm() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_encryptionAlgorithm;
    }

    bool ProductKeyGenerator::setEncryptionAlgorithm(const std::shared_ptr<IEncryptionAlgorithm>& newEncryptionAlgorithm)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (newEncryptionAlgorithm == nullptr)
        {
            std::cerr << "Warning: Failed to set EncryptionAlgorithm because it is null." << std::endl;
            return false;
        }

        m_encryptionAlgorithm = newEncryptionAlgorithm;
        return true;
    }
} // namespace PKF