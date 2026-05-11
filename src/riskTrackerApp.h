/* Brandon Zuniga */
/* Revised 4/5/2026 */
#pragma once

#include <string>
#include <memory>
#include <Wt/WApplication.h>
#include <Wt/WTimer.h>
//#include <Wt/WTime.h>

// Forward declarations for the managers
class DatabaseManager;
class Authenticator;
class UserManager;
class RiskManager;
class ProjectManager;

class riskTrackerApp : public Wt::WApplication {
public:
    riskTrackerApp() = delete;
    explicit riskTrackerApp(const Wt::WEnvironment &env);
    
    // UI Navigation
    void handleLoginSuccess(const std::string& username);
    void showDashboard(); // View may need to change name
    void logout();
    void updateActivity();

    // Getters so Views can access the Models to fetch/push data
    std::shared_ptr<UserManager> getUserManager() { 
	return userManager_;
    }
    std::shared_ptr<RiskManager> getRiskManager() { 
	    return riskManager_; 
    }
    std::shared_ptr<ProjectManager> getProjectManager() {
        return projectManager_;
    }
    std::shared_ptr<DatabaseManager> getDatabaseManager() {
        return dbManager_;
    }
private:
    void createLoginContainer();
    std::string appName;

    // Core Backend Managers instantiated once per session 
    std::shared_ptr<DatabaseManager> dbManager_;
    std::shared_ptr<Authenticator> auth_;
    std::shared_ptr<UserManager> userManager_;
    std::shared_ptr<RiskManager> riskManager_;
    std::shared_ptr<ProjectManager> projectManager_;

    std::unique_ptr<Wt::WTimer> idleTimer_;
    std::chrono::steady_clock::time_point lastActivity_;

};
