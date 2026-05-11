/* Josh Nettle */
/* 4/7/2026 */
#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "riskManagerModel.h"
#include "databaseManagerModel.h"
#include "riskItemModel.h"
#include "projectModel.h"

class RiskManagerTest : public ::testing::Test {
protected:
	std::shared_ptr<DatabaseManager> db;
	std::unique_ptr<RiskManager> manager;

	void SetUp() override {
		db = std::make_shared<DatabaseManager>();
		manager = std::make_unique<RiskManager>(db);
	}
};

TEST_F(RiskManagerTest, ConstructorState) {
	EXPECT_EQ(manager->getStatus(), "Initialized");
	EXPECT_EQ(manager->getNewData(), "");
}

TEST_F(RiskManagerTest, AddRiskIntegration) {
	std::string name = "IntegrationRisk";
	std::string desc = "Testing DB insertion";
	int probability = 4;
	int impact = 5;

	manager->addRisk(name, desc, probability, impact);

	EXPECT_EQ(manager->getStatus(), "Risk created successfully");

	std::vector<RiskItem> risks = db->getRisksByProject(0);
	bool found = false;
	for (const auto& r : risks) {
		if (r.getRiskName() == name) {
			EXPECT_EQ(r.getProbability(), probability);
			EXPECT_EQ(r.getImpact(), impact);
			found = true;
			break;
		}
	}
		
	EXPECT_TRUE(found) << "Risk was not found in database after addRisk call";
}

TEST_F(RiskManagerTest, UpdateRiskIntegration) {
	RiskItem initialRisk;
	initialRisk.setRiskName("OldName");
	initialRisk.setProjectID(99);
	db->addRisk(initialRisk);

	auto allRisks = db->getRisksByProject(99);
	ASSERT_FALSE(allRisks.empty());
	int targetId = allRisks[0].getRiskID();

	std::string updatedData = "UpdatedMetadata";
	manager->updateRisk(targetId, updatedData);

	EXPECT_EQ(manager->getStatus(), "Risk updated");
	EXPECT_EQ(manager->getNewData(), updatedData);

	RiskItem check = db->getRiskById(targetId);
	EXPECT_EQ(check.getDesc(), updatedData);
}

TEST_F(RiskManagerTest, ListRisksIntegration) {
	int testProjectId = 777;
	
	RiskItem r1;
	r1.setRiskName("Risk 1");
	r1.setProjectID(testProjectId);
	db->addRisk(r1);

	std::vector<RiskItem> results = manager->listRisks(testProjectId);

	EXPECT_FALSE(results.empty());
	EXPECT_EQ(results.size(), 1);
	EXPECT_EQ(results[0].getRiskName(), "Risk 1");
}

TEST_F(RiskManagerTest, GettersAndSetters) {
	manager->setStatus("CustomStatus");
	manager->setNewData("SomeData");

	EXPECT_EQ(manager->getStatus(), "CustomStatus");	
	EXPECT_EQ(manager->getNewData(), "SomeData");
}
