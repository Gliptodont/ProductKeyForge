#include "PKF.h"
#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"

namespace PKF
{
    class LinearCongruentialGeneratorTest : public ::testing::Test
    {
    protected:
        LinearCongruentialGenerator generator;

        void SetUp() override
        {
            generator.init();
        }
    };

    TEST_F(LinearCongruentialGeneratorTest, InitSetsSeedAndCurrent)
    {
        EXPECT_NO_THROW(generator.init());
    }

    TEST_F(LinearCongruentialGeneratorTest, InitWithSeedSetsSeedAndCurrent)
    {
        unsigned int seed = 12345;
        EXPECT_NO_THROW(generator.initWithSeed(seed));
    }

    TEST_F(LinearCongruentialGeneratorTest, InitWithSeedZeroDefaultsToCurrentTime)
    {
        EXPECT_NO_THROW(generator.initWithSeed(0));
    }

    TEST_F(LinearCongruentialGeneratorTest, GetRandomCharacterReturnsValidCharacter)
    {
        std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        auto randomChar = generator.getRandomCharacter(characters);
        EXPECT_TRUE(randomChar.has_value());
        EXPECT_NE(characters.find(randomChar.value()), std::string::npos);
    }

    TEST_F(LinearCongruentialGeneratorTest, GetRandomCharacterWithEmptyStringReturnsNullopt)
    {
        std::string characters = "";
        auto randomChar = generator.getRandomCharacter(characters);
        EXPECT_FALSE(randomChar.has_value());
    }
}