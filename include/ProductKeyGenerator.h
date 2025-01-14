#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <ranges>

#include "KeyFormat.h"

#include "RandomGenerator/IRandomGenerator.h"
#include "RandomGenerator/MTRandomGenerator.h"

#include "Checksum/IChecksumAlgorithm.h"
#include "Checksum/BaseChecksumAlgorithm.h"

namespace PKF
{
    class KeyFormat;
    class IRandomGenerator;

    //TODO: ПРОВЕРЬ БЕЗОПАСТНОСТЬ В МНОГОПОТОЧНОЙ СРЕДЕ
    class ProductKeyGenerator
    {
    public:
        ProductKeyGenerator();
        explicit ProductKeyGenerator(const std::shared_ptr<KeyFormat>& keyFormat, const std::shared_ptr<IRandomGenerator>& randomGenerator)
            : m_keyFormat(keyFormat)
            , m_randomGenerator(randomGenerator)
        {
            if (m_keyFormat == nullptr)
            {
                std::cerr << "Warning: KeyFormat is null, setting to default." << std::endl;
                m_keyFormat = std::make_shared<KeyFormat>();
            }

            if (m_randomGenerator == nullptr)
            {
                std::cerr << "Warning: RandomGenerator is null, setting to default." << std::endl;
                m_randomGenerator = std::make_shared<MTRandomGenerator>();
                m_randomGenerator->init();
            }
        }

        [[nodiscard]] std::optional<std::string> generateKey() const;
        [[nodiscard]] std::vector<std::string> getKeyBySegments(std::string_view key) const;


        [[nodiscard]] std::shared_ptr<KeyFormat> getKeyFormat() const;
        bool setKeyFormat(const std::shared_ptr<KeyFormat>& newKeyFormat);
        [[nodiscard]] std::shared_ptr<IRandomGenerator> getRandomGenerator() const;
        bool setRandomGenerator(const std::shared_ptr<IRandomGenerator>& newRandomGenerator);
        [[nodiscard]] std::shared_ptr<IChecksumAlgorithm> getChecksumAlgorithm() const;
        bool setChecksumAlgorithm(const std::shared_ptr<IChecksumAlgorithm>& newChecksumAlgorithm);

    private:
        std::shared_ptr<KeyFormat> m_keyFormat;
        std::shared_ptr<IRandomGenerator> m_randomGenerator;
        mutable std::shared_ptr<IChecksumAlgorithm> m_checksumAlgorithm;

        mutable std::mutex m_mutex;

        [[nodiscard]] std::optional<std::string> generateSegment(size_t length) const;
    };
} // namespace PKF