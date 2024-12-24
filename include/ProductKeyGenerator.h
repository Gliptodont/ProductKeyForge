#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>
#include <mutex>

#include "RandomGenerator/IRandomGenerator.h"

#include <vector>

namespace PKF
{
    namespace Defaults
    {
        // Default values for KeyFormat configuration
        static constexpr std::string DEFAULT_CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        static constexpr size_t DEFAULT_SEGMENT_LENGTH = 5;
        static constexpr size_t DEFAULT_SEGMENT_COUNT = 5;
        static constexpr char DEFAULT_SEPARATOR = '-';
    }

    struct KeyFormat
    {
        std::string m_characters;
        size_t m_segmentLength;
        size_t m_segmentCount;
        bool m_hasCheckSum;
        char m_separator;

        explicit KeyFormat(
            const std::string& characters = Defaults::DEFAULT_CHARACTERS,
            const size_t segmentLength = Defaults::DEFAULT_SEGMENT_LENGTH,
            const size_t segmentCount = Defaults::DEFAULT_SEGMENT_COUNT,
            const bool hasCheckSum = false,
            const char separator = Defaults::DEFAULT_SEPARATOR)
            : m_characters(characters),
              m_segmentLength(segmentLength),
              m_segmentCount(segmentCount),
              m_hasCheckSum(hasCheckSum),
              m_separator(separator)
        {
        }
    };

    class IRandomGenerator;

    class ProductKeyGenerator
    {
    public:
        explicit ProductKeyGenerator(
            const std::shared_ptr<KeyFormat>& keyFormat,
            const std::shared_ptr<IRandomGenerator>& randomGenerator)
            : m_keyFormat(keyFormat),
              m_randomGenerator(randomGenerator)
        {
            if (m_keyFormat == nullptr)
            {
                std::cerr << "Warning: KeyFormat is null, setting to default." << std::endl;
                m_keyFormat = std::make_shared<KeyFormat>();
            }

            if (m_randomGenerator == nullptr)
            {
                std::cerr << "Warning: RandomGenerator is null, setting to default." << std::endl;
                //m_randomGenerator = std::make_shared<IRandomGenerator>();
            }
        }

        [[nodiscard]] std::string generateKey() const;
        [[nodiscard]] std::vector<std::string> generateKeyBySegments() const;

        bool setKeyFormat(const std::shared_ptr<KeyFormat>& newKeyFormat);
        bool setRandomGenerator(const std::shared_ptr<IRandomGenerator>& newRandomGenerator);

    private:
        std::shared_ptr<KeyFormat> m_keyFormat;
        std::shared_ptr<IRandomGenerator> m_randomGenerator;

        std::mutex m_mutex;
    };
}