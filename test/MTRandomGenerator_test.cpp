#include "PKF.h"
#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"

namespace PKF
{
    class MTRandomGeneratorTest : public ::testing::Test
    {
    protected:
        MTRandomGenerator generator;

        void SetUp() override
        {
            generator.init();
        }
    };

    TEST_F(MTRandomGeneratorTest, Init)
    {
        EXPECT_NO_THROW(generator.init());
    }

    TEST_F(MTRandomGeneratorTest, GetRandomCharacter)
    {
        std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        auto randomChar = generator.getRandomCharacter(characters);
        EXPECT_TRUE(randomChar.has_value());
        EXPECT_NE(characters.find(randomChar.value()), std::string::npos);

        randomChar = generator.getRandomCharacter("");
        EXPECT_FALSE(randomChar.has_value());
    }
}