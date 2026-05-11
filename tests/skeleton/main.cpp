#include <gtest/gtest.h>
#include "wittyTest.h"

// test logic
namespace {
    TEST(WittyModel, constructor) {
        witty::WittyTest myTest;
        EXPECT_EQ("", myTest.getStatus());
    }

    TEST(WittyModel, process_click_logic) {
        witty::WittyTest myTest;
        myTest.processClick();
        EXPECT_EQ("it works", myTest.getStatus());
    }
}
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
