/* Josh Nettle */
/* 05/03/2026 */
#include <gtest/gtest.h>
#include <memory>
#include "riskItemModel.h"
#include "databaseManagerModel.h"

class RiskItemTest : public ::testing::Test {
protected: 
	std::shared_ptr<DatabaseManager> db;

	void SetUp() override {
		db = std::make_shared<DatabaseManager>();
	}
};

TEST_F(RiskItemTest, SettersAndGetters) {
	RiskItem risk;
	
	risk.setRiskName("Data Leak");
	risk.setDesc("Potential exposure of customer PII");
	risk.setProbability(3);
	risk.setImpact(5);
	risk.setProjectID(101);

	EXPECT_EQ(risk.getRiskName(), "Data Leak");
	EXPECT_EQ(risk.getDesc(), "Potential exposure of customer PII");
	EXPECT_EQ(risk.getProbability(), 3);
	EXPECT_EQ(risk.getImpact(), 5);
	EXPECT_EQ(risk.getProjectID(), 101);
}

TEST_F(RiskItemTest, DatabasePersistence) {
	RiskItem originalRisk;
	originalRisk.setRiskName("Server Failure");
	originalRisk.setDesc("Hardware failure in primary data center");
	originalRisk.setProbability(2);
	originalRisk.setImpact(4);
	originalRisk.setProjectID(1);

	db->addRisk(originalRisk);

	std::vector<RiskItem> risks = db->getRisksByProject(1);

	ASSERT_FALSE(risks.empty());

	bool found = false;
	for (const auto& r : risks) {
		if (r.getRiskName() == "Server Failure") {
			EXPECT_EQ(r.getProbability(), 2);
			EXPECT_EQ(r.getImpact(), 4);
			found = true;
			break;
		}
	}

	EXPECT_TRUE(found) << "The RiskItem was not found in the database after insersion.";
}

TEST_F(RiskItemTest, EditRiskPersistence) {
	RiskItem risk;
	risk.setRiskName("Initial Risk");
	risk.setProjectID(2);
	db->addRisk(risk);

	std::vector<RiskItem> risks = db->getRisksByProject(2);
	RiskItem toEdit= risks[0];
	int dbId = toEdit.getRiskID();

	toEdit.setRiskName("Updated Risk Name");
	db->editRisk(toEdit);

	RiskItem verified = db->getRiskById(dbId);
	EXPECT_EQ(verified.getRiskName(), "Updated Risk Name");
}
