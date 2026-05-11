/* Brandon Zuniga */
/* 2/12/2026 (Refactored) */
#include "projectManagerModel.h"
#include "databaseManagerModel.h"

ProjectManager::ProjectManager(std::shared_ptr<DatabaseManager> db) 
    : dbManager_(db) {}

bool ProjectManager::addProject(Project& project) {
    if (!dbManager_) 
	    return false;
    
    // Pass the entire project object to the database
    dbManager_->addProject(project); 
    return true; 
}

bool ProjectManager::updateProject(Project& project) {
    if (!dbManager_ || project.getID() == -1) 
	    return false;
    
    // Pass the object to be edited
    dbManager_->editProject(project);
    return true;
}

bool ProjectManager::deleteProject(Project& project) {
    if (!dbManager_ || project.getID() == -1) 
	    return false;
    
    // Pass the object to be deleted
    dbManager_->deleteProject(project);
    return true;
}

Project ProjectManager::getProject(int id) {
    if (!dbManager_) return Project(); // Return an empty, invalid project if no DB
    
    // Retrieve the fully populated project object from the database
    return dbManager_->getProjectByID(id);
}

std::vector<Project> ProjectManager::getAllProjects() {
    if (!dbManager_) return {};
    return dbManager_->getAllProjects();
}
