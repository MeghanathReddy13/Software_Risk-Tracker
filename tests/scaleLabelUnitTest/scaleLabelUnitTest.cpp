/*
 * Shelby Stanly
 * Scale Label Test
 * Date: 4/23/2026
 * Updated: 5/3/2026
 */
#include <gtest/gtest.h>
#include "scaleLabelModel.h"

namespace dbo = Wt::Dbo;

TEST(ScaleLabelUnitTest, GetandSet) {
    ScaleLabel label;

    label.setName("High Impact");
    label.setId(69);
    label.setLevel(5);
    label.setType(1);

    EXPECT_EQ(label.getName(), "High Impact");
    EXPECT_EQ(label.getId(), 69);
    EXPECT_EQ(label.getLevel(), 5);
    EXPECT_EQ(label.getType(), 1);
}

TEST(ScaleLabelUnitTest, ConstructorInit) {
    ScaleLabel label(0, nullptr, 2, "Medium Impact", 3);

    EXPECT_EQ(label.getName(), "Medium Impact");
    EXPECT_EQ(label.getLevel(), 3);
    EXPECT_EQ(label.getType(), 2);
}

TEST(ScaleLabelUnitTest, ProjectAssignment) {
    ScaleLabel label;

    dbo::ptr<Project> projectPtr;
    label.setProject(projectPtr);

    EXPECT_EQ(label.getProject(), projectPtr);
}
