#include "PKF.h"
#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"

namespace PKF
{
    class XorshiftGeneratorTest : public ::testing::Test
    {
    protected:
        XorshiftGenerator generator;

        void SetUp() override
        {
            generator.init();
        }
    };

    TEST_F(XorshiftGeneratorTest, InitSetsState)
    {
        EXPECT_NO_THROW(generator.init());
    }

    TEST_F(XorshiftGeneratorTest, InitWithSeedSetsState)
    {
        uint32_t seed = 12345;
        EXPECT_NO_THROW(generator.initWithSeed(seed));
    }

    TEST_F(XorshiftGeneratorTest, InitWithSeedZeroDefaultsToCurrentTime)
    {
        EXPECT_NO_THROW(generator.initWithSeed(0));
    }

    TEST_F(XorshiftGeneratorTest, GetRandomCharacterReturnsValidCharacter)
    {
        std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        auto randomChar = generator.getRandomCharacter(characters);
        EXPECT_TRUE(randomChar.has_value());
        EXPECT_NE(characters.find(randomChar.value()), std::string::npos);
    }

    TEST_F(XorshiftGeneratorTest, GetRandomCharacterWithEmptyStringReturnsNullopt)
    {
        std::string characters = "";
        auto randomChar = generator.getRandomCharacter(characters);
        EXPECT_FALSE(randomChar.has_value());
    }
}