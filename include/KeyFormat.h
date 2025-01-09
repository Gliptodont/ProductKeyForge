#pragma once

#include <iostream>
#include <mutex>
#include <string>
#include <unordered_set>

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
        {
        }

        [[nodiscard]] std::string getCharacters();
        bool setCharacters(const std::string& characters);
        [[nodiscard]] size_t getSegmentLength();
        bool setSegmentLength(size_t length);
        [[nodiscard]] size_t getSegmentCount();
        bool setSegmentCount(size_t count);
        [[nodiscard]] char getSeparator();
        bool setSeparator(char separator);

        [[nodiscard]] bool validate() const;

    private:
        std::string m_characters;
        size_t m_segmentLength;
        size_t m_segmentCount;
        char m_separator;

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