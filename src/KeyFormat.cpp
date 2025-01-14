#include "KeyFormat.h"

namespace PKF
{

    std::string KeyFormat::getCharacters()
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        return std::string(m_characters);
    }

    bool KeyFormat::setCharacters(const std::string& characters)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (characters.empty())
        {
            std::cerr << "Warning: Characters cannot be empty." << std::endl;
            return false;
        }
        else if (!validateRange(characters.size(), static_cast<size_t>(2), static_cast<size_t>(256), "Warning: Characters size must be between 2 and 256."))
        {
            return false;
        }

        std::unordered_set<char> uniqueChars(characters.begin(), characters.end());
        if (uniqueChars.size() != characters.size())
        {
            std::cerr << "Warning: Characters must not contain duplicates." << std::endl;
            return false;
        }

        m_characters = characters;
        return true;
    }

    size_t KeyFormat::getSegmentLength() const
    {
        return m_segmentLength.load();
    }

    bool KeyFormat::setSegmentLength(size_t length)
    {
        if (!validateRange(length, static_cast<size_t>(1), static_cast<size_t>(50), "Warning: Segment length must be between 1 and 50."))
        {
            return false;
        }

        m_segmentLength.store(length);
        return true;
    }

    size_t KeyFormat::getSegmentCount() const
    {
        return m_segmentCount.load();
    }

    bool KeyFormat::setSegmentCount(size_t count)
    {
        if (!validateRange(count, static_cast<size_t>(1), static_cast<size_t>(20), "Warning: Segment count must be between 1 and 20."))
        {
            return false;
        }

        m_segmentCount.store(count);
        return true;
    }

    char KeyFormat::getSeparator() const
    {
        return m_separator.load();
    }

    bool KeyFormat::setSeparator(char separator)
    {
        if (separator == '\0')
        {
            std::cerr << "Warning: Separator cannot be null." << std::endl;
            return false;
        }

        {
            std::lock_guard<std::mutex> lock(m_mutex);

            if (m_characters.find(separator) != std::string_view::npos)
            {
                std::cerr << "Warning: Separator must not be a part of the character set." << std::endl;
                return false;
            }
        }

        m_separator.store(separator);
        return true;
    }

    bool KeyFormat::getHasChecksum() const
    {
        return m_hasChecksum.load();
    }

    void KeyFormat::setHasChecksum(bool isChecksum)
    {
        m_hasChecksum.store(isChecksum);
    }

    bool KeyFormat::validate() const
    {
        size_t totalKeyLength = getSegmentLength() * getSegmentCount() + (getSegmentCount() - 1);

        if (totalKeyLength > 1024)
        {
            std::cerr << "Warning: Combined key length too large." << std::endl;
            return false;
        }

        return true;
    }
} // namespace PKF