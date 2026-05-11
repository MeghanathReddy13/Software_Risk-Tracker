/* Brandon Zuniga */
/* 2/12/2026 (Refactored) */
#ifndef PROJECT_MANAGER_MODEL_H
#define PROJECT_MANAGER_MODEL_H

#include <memory>
#include "projectModel.h"

// Forward declare DatabaseManager to prevent circular dependencies
class DatabaseManager; 

class ProjectManager {
public:
    // Constructor
    ProjectManager(std::shared_ptr<DatabaseManager> db); 
    
    // Core Manager Methods (now take/return Project objects)
    bool addProject(Project& project); 
    bool updateProject(Project& project);
    bool deleteProject(Project& project); // SDD explicitly defines this taking a Project
    
    Project getProject(int id);
    std::vector<Project> getAllProjects();
private:
    std::shared_ptr<DatabaseManager> dbManager_; 
};

#endif // PROJECT_MANAGER_MODEL_H
