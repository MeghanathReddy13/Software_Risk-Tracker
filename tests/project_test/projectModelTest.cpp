#include <gtest/gtest.h>
#include <chrono>
#include <vector>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include "projectModel.h"

class ProjectModelTest : public ::testing::Test {
protected: 
	void SetUp() override {
		auto sqlite3 = std::make_unique<Wt::Dbo::backend::Sqlite3>(":memory:");
		session.setConnection(std::move(sqlite3));
		session.mapClass<Project>("project");
		session.mapClass<RiskItem>("risk_item");

		{
			Wt::Dbo::Transaction t(session);
			session.createTables();
			t.commit();
		}
	}

	Wt::Dbo::Session session;
};

TEST_F(ProjectModelTest, GettersAndSetters) {
	Project p;
	auto now = std::chrono::system_clock::now();

	p.setName("Infrastructure Overhaul");
	p.setImpactCount(10);
	p.setProbCount(3);
	p.setCreated(now);
	p.setModified(now);
	
	EXPECT_EQ(p.getName(), "Infrastructure Overhaul");
	EXPECT_EQ(p.getImpactCount(), 10);
	EXPECT_EQ(p.getProbCount(), 3);
	EXPECT_EQ(p.getCreated(), now);
	EXPECT_EQ(p.getModified(), now);
}

TEST_F(ProjectModelTest, DatabasePersistence) {
	auto now = std::chrono::system_clock::now();
	std::string projName = "Persistence Test Project";

	{
		Wt::Dbo::Transaction t(session);
		auto project = std::make_unique<Project>();
		project->setName(projName);
		project->setImpactCount(7);	
		project->setProbCount(2);
		project->setCreated(now);
		session.add(std::move(project));
		t.commit();
	}

	{
		Wt::Dbo::Transaction t(session);
		Wt::Dbo::ptr<Project> retrieved = session.find<Project>().where("name = ?").bind(projName);

		ASSERT_TRUE(retrieved);
		EXPECT_EQ(retrieved->getName(), projName);
		EXPECT_EQ(retrieved->getImpactCount(), 7);
		EXPECT_EQ(retrieved->getProbCount(), 2);
		t.commit();
	}
}

TEST_F(ProjectModelTest, DefaultValues) {
	Project p;
	EXPECT_EQ(p.getID(), -1);
	EXPECT_EQ(p.getImpactCount(), 5);
	EXPECT_EQ(p.getProbCount(), 5);
}
