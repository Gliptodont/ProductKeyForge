#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <ranges>
#include <atomic>

#include "KeyFormat.h"

#include "RandomGenerator/IRandomGenerator.h"
#include "RandomGenerator/MTRandomGenerator.h"

#include "Checksum/IChecksumAlgorithm.h"
#include "Checksum/BaseChecksumAlgorithm.h"

namespace PKF
{
    class KeyFormat;
    class IRandomGenerator;

    class ProductKeyGenerator
    {
    public:
        ProductKeyGenerator();

        explicit ProductKeyGenerator(const std::shared_ptr<KeyFormat>& keyFormat, const std::shared_ptr<IRandomGenerator>& randomGenerator)
            : m_keyFormat(keyFormat)
            , m_randomGenerator(randomGenerator)
            , m_checksumAlgorithm(nullptr)
        {
            if (m_keyFormat.load() == nullptr)
            {
                std::cerr << "Warning: KeyFormat is null, setting to default." << std::endl;
                m_keyFormat.store(std::make_shared<KeyFormat>());
            }

            if (m_randomGenerator.load() == nullptr)
            {
                std::cerr << "Warning: RandomGenerator is null, setting to default." << std::endl;
                m_randomGenerator.store(std::make_shared<MTRandomGenerator>());
                m_randomGenerator.load()->init();
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
        mutable std::mutex m_mutex;
        std::atomic<std::shared_ptr<KeyFormat>> m_keyFormat;
        std::atomic<std::shared_ptr<IRandomGenerator>> m_randomGenerator;
        mutable std::atomic<std::shared_ptr<IChecksumAlgorithm>> m_checksumAlgorithm;

        [[nodiscard]] std::optional<std::string> generateSegment(size_t length) const;
    };
} // namespace PKF