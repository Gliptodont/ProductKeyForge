#pragma once

#include <string>
#include <optional>

namespace PKF
{
    class IRandomGenerator
    {
    public:
        virtual ~IRandomGenerator() = default;

        virtual void init() = 0;

        virtual std::optional<char> getRandomCharacter(const std::string&) = 0;
    };
} // namespace PKF