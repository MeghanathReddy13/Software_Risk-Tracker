/* Josh Nettle */
/* 05/03/2026 */
#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "projectManagerModel.h"
#include "databaseManagerModel.h"
#include "projectModel.h"

class ProjectManagerTest : public ::testing::Test {
	protected:
	std::shared_ptr<DatabaseManager> db;
	std::unique_ptr<ProjectManager> projectMgr;

	void SetUp() override {
		db = std::make_shared<DatabaseManager>();
		projectMgr = std::make_unique<ProjectManager>(db);
	}
};

TEST_F(ProjectManagerTest, AddProjectSuccess) {
	Project p;
	p.setName("New Construction Project");
	p.setImpactCount(5);
	p.setProbCount(5);

	EXPECT_TRUE(projectMgr->addProject(p));
	
	auto allProjects = projectMgr->getAllProjects();
	bool found = false;
	for (const auto& proj : allProjects) {
		if (proj.getName() == "New Construction Project") {
			found = true;
			break;
		}
	}
	EXPECT_TRUE(found);
}

TEST_F(ProjectManagerTest, UpdateProjectSuccess) {
	Project p; 
	p.setName("Old Name");
	projectMgr->addProject(p);

	auto list = projectMgr->getAllProjects();
	Project toUpdate = list.back();
	
	toUpdate.setName("New Improved Name");
	EXPECT_TRUE(projectMgr->updateProject(toUpdate));
	
	Project verified = projectMgr->getProject(toUpdate.getID());
	EXPECT_EQ(verified.getName(), "New Improved Name");
}

TEST_F(ProjectManagerTest, DeleteProjectSuccess) {
	Project p;
	p.setName("To Be Deleted");
	projectMgr->addProject(p);

	auto list = projectMgr->getAllProjects();
	Project toDelete = list.back();

	EXPECT_TRUE(projectMgr->deleteProject(toDelete));

	bool stillExists = true;
	try {
		Project missing = projectMgr->getProject(toDelete.getID());
		
		if (missing.getID() == -1) {
			stillExists = false;
		}
	    }
	catch (...) {
		stillExists = false;
	}

	EXPECT_FALSE(stillExists) << "Project still exists in DB after deletion!";
}

TEST_F(ProjectManagerTest, HandleInvalidProjectID) {
	Project p;
	p.setID(-1);

	EXPECT_FALSE(projectMgr->updateProject(p));
	EXPECT_FALSE(projectMgr->deleteProject(p));
}
