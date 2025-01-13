#pragma once

#include <string>

#include "KeyFormat.h"

namespace PKF
{
    class IChecksumAlgorithm
    {
    public:
        virtual ~IChecksumAlgorithm() = default;

        virtual int calculate(const std::string&, const char&) const = 0;
        virtual bool validate(const std::string&, const char&) const = 0;
    };
}