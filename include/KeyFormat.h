#pragma once

#include <iostream>
#include <mutex>
#include <string>
#include <unordered_set>
#include <atomic>

namespace PKF
{
    namespace Defaults
    {
        // Default values for KeyFormat configuration
        constexpr std::string_view DEFAULT_CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        constexpr size_t DEFAULT_SEGMENT_LENGTH = 5;
        constexpr size_t DEFAULT_SEGMENT_COUNT = 5;
        constexpr char DEFAULT_SEPARATOR = '-';
    } // namespace Defaults

    class KeyFormat
    {
    public:
        KeyFormat()
            : m_characters(std::string(Defaults::DEFAULT_CHARACTERS))
            , m_segmentLength(Defaults::DEFAULT_SEGMENT_LENGTH)
            , m_segmentCount(Defaults::DEFAULT_SEGMENT_COUNT)
            , m_separator(Defaults::DEFAULT_SEPARATOR)
            , m_hasChecksum(false)
        {
        }

        [[nodiscard]] std::string getCharacters();
        bool setCharacters(const std::string& characters);
        [[nodiscard]] size_t getSegmentLength() const;
        bool setSegmentLength(size_t length);
        [[nodiscard]] size_t getSegmentCount() const;
        bool setSegmentCount(size_t count);
        [[nodiscard]] char getSeparator() const;
        bool setSeparator(char separator);
        [[nodiscard]] bool getHasChecksum() const;
        void setHasChecksum(bool isChecksum);

        [[nodiscard]] bool validate() const;

    private:
        std::string m_characters;
        std::atomic<size_t> m_segmentLength;
        std::atomic<size_t> m_segmentCount;
        std::atomic<char> m_separator;
        std::atomic<bool> m_hasChecksum;

        mutable std::mutex m_mutex;

        template<typename T>
        bool validateRange(T value, T min, T max, const std::string& errorMessage)
        {
            if (value < min || value > max)
            {
                std::cerr << errorMessage << std::endl;
                return false;
            }
            return true;
        }
    };
} // namespace PKF