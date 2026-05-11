#include <gtest/gtest.h>
#include "projectModel.h"
#include "riskItemModel.h"

// Test A: Matrix Dimensions (Requirement FUNC-4)
TEST(ProjectModelTest, DefaultMatrixSize) {
    Project proj;

    EXPECT_EQ(proj.getImpactCount(), 5);
    EXPECT_EQ(proj.getProbCount(), 5);
}

TEST(RiskItemModelTest, DataIntegrity) {
    RiskItem risk;

    // Set values according to FUNC-3 (ID, Description, Likelihood, Impact)
    risk.setRiskID(101);
    risk.setRiskName("Database Timeout");
    risk.setDesc("The server takes too long to respond to SQL queries.");
    risk.setProbability(3);
    risk.setImpact(4);

    EXPECT_EQ(risk.getRiskID(), 101);
    EXPECT_EQ(risk.getRiskName(), "Database Timeout");
    EXPECT_EQ(risk.getDesc(), "The server takes too long to respond to SQL queries.");
    EXPECT_EQ(risk.getProbability(), 3);
    EXPECT_EQ(risk.getImpact(), 4);
}

// Test C: Project Metadata (Requirement FUNC-1)
TEST(ProjectModelTest, InitializationState) {
    Project proj;
    EXPECT_EQ(proj.getID(), -1);

    proj.setName("Risk Tracker 2026");
    EXPECT_EQ(proj.getName(), "Risk Tracker 2026");
}
