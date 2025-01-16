#include "PKF.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace PKF
{
    TEST(KeyFormatTest, DefaultConstructor) {
        KeyFormat keyFormat;
        EXPECT_EQ(keyFormat.getCharacters(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
        EXPECT_EQ(keyFormat.getSegmentLength(), 5);
        EXPECT_EQ(keyFormat.getSegmentCount(), 5);
        EXPECT_EQ(keyFormat.getSeparator(), '-');
        EXPECT_FALSE(keyFormat.getHasChecksum());
    }

    TEST(KeyFormatTest, SetCharacters) {
        KeyFormat keyFormat;
        EXPECT_TRUE(keyFormat.setCharacters("ABCD1234"));
        EXPECT_EQ(keyFormat.getCharacters(), "ABCD1234");

        EXPECT_FALSE(keyFormat.setCharacters(""));
        EXPECT_FALSE(keyFormat.setCharacters("A"));
        EXPECT_FALSE(keyFormat.setCharacters("AABCD1234"));
    }

    TEST(KeyFormatTest, SetSegmentLength) {
        KeyFormat keyFormat;
        EXPECT_TRUE(keyFormat.setSegmentLength(10));
        EXPECT_EQ(keyFormat.getSegmentLength(), 10);

        EXPECT_FALSE(keyFormat.setSegmentLength(0));
        EXPECT_FALSE(keyFormat.setSegmentLength(51));
    }

    TEST(KeyFormatTest, SetSegmentCount) {
        KeyFormat keyFormat;
        EXPECT_TRUE(keyFormat.setSegmentCount(10));
        EXPECT_EQ(keyFormat.getSegmentCount(), 10);

        EXPECT_FALSE(keyFormat.setSegmentCount(0));
        EXPECT_FALSE(keyFormat.setSegmentCount(21));
    }

    TEST(KeyFormatTest, SetSeparator) {
        KeyFormat keyFormat;
        EXPECT_TRUE(keyFormat.setSeparator('_'));
        EXPECT_EQ(keyFormat.getSeparator(), '_');

        EXPECT_FALSE(keyFormat.setSeparator('\0'));
        EXPECT_FALSE(keyFormat.setSeparator('A'));
    }

    TEST(KeyFormatTest, SetHasChecksum) {
        KeyFormat keyFormat;
        keyFormat.setHasChecksum(true);
        EXPECT_TRUE(keyFormat.getHasChecksum());

        keyFormat.setHasChecksum(false);
        EXPECT_FALSE(keyFormat.getHasChecksum());
    }
}
