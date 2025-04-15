#include <gtest/gtest.h>
#include "main.h"

TEST(FunctionsTest, Encoding) {
    std::string to_encode = "star";
    std::string encoded = encode(to_encode);
    EXPECT_EQ(encoded, "F*(i2");
}

TEST(FunctionsTest, Decoding) {
    std::string to_decode = "F*(i2";
    std::string decoded = decode(to_decode);
    EXPECT_EQ(decoded, "star");
}

int main (int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
