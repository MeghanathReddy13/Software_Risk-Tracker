/* Brandon Zuniga */
/* Revised 4/5/2026 */
#include "riskTrackerApp.h"
#include "loginView.h" 
#include "navView.h"
#include "projectNavView.h"
#include "databaseManagerModel.h"
#include "authManagerModel.h"
#include "userManagerModel.h"
#include "riskManagerModel.h"
#include "projectManagerModel.h"

#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>

namespace AppConfig {
    static constexpr int MAX_IDLE_TIME_SECONDS = 900;
}

using namespace Wt;

riskTrackerApp::riskTrackerApp(const Wt::WEnvironment& env)
    : WApplication{env}, appName{"Risk Tracker"}
{
    setTitle(appName);
    useStyleSheet("src/view/style.css");
    useStyleSheet("src/view/projectNavView.css");
    useStyleSheet("src/view/riskAddForm.css");
    useStyleSheet("src/view/riskMatrixView.css");

    // Instantiate the Database and Authenticator first (Dependencies)
    dbManager_ = std::make_shared<DatabaseManager>();
    auth_ = std::make_shared<Authenticator>(dbManager_);

    // Instantiate the Managers, injecting the dependencies
    userManager_ = std::make_shared<UserManager>(dbManager_, auth_);//auth_);

    userManager_->setOnActivity([this]() 
    {
        updateActivity();
    });

    riskManager_ = std::make_shared<RiskManager>(dbManager_);
    projectManager_ = std::make_shared<ProjectManager>(dbManager_);

    // added hard coded user for practice.  REMOVE THIS once database is integrated
    // NG 04/04
    //User admin;
    //admin.setName("Admin");
    //admin.setUserName("admin");
    //admin.setPassHash(auth_->generateHash("admin"));
    //dbManager_->addUser(admin);

/*
    // Connect the inactivity timeout signal to the UserManager
    this->idleTimeout().connect([this]() {
        userManager_->idleTimer();
        root()->clear();
        createLoginContainer(); // Kick them back to login on timeout
    });
*/

    User existing = dbManager_->getUserByIdentity("admin");
    idleTimer_ = std::make_unique<Wt::WTimer>();
    idleTimer_->setInterval(std::chrono::seconds(AppConfig::MAX_IDLE_TIME_SECONDS));

    idleTimer_->timeout().connect([this]() {
            idleTimer_->stop();
            userManager_->idleTimer();
	if(!userManager_->isLoggedIn()){
            root()->clear();
            createLoginContainer();
	}
    });

    idleTimer_->start();

    lastActivity_ = std::chrono::steady_clock::now();
    idleTimer_ = std::make_unique<Wt::WTimer>();
    idleTimer_->setInterval(std::chrono::seconds(1));
    idleTimer_->timeout().connect([this]() {
        auto now = std::chrono::steady_clock::now();
        auto idleSeconds = std::chrono::duration_cast<std::chrono::seconds>(now-lastActivity_).count();
        if (idleSeconds >= AppConfig::MAX_IDLE_TIME_SECONDS) {
            //idleTimer_->stop();
            userManager_->idleTimer();
            root()->clear();
            createLoginContainer();
        }
    });

    idleTimer_->start();

    
    //Create default admin user
	if(existing.getID() < 0){
	User admin;
        admin.setName("admin");
        admin.setUserName("admin");
        admin.setPassHash(auth_->generateHash("admin"));
        admin.setRole({"ADMIN"});
	dbManager_->addUser(admin);
	}

    root()->clicked().connect([this]() {updateActivity(); });
    root()->keyWentDown().connect([this](const WKeyEvent&) {updateActivity(); });

    // Load the initial view
    root()->clear();
    createLoginContainer(); // Placeholder for now
}

void riskTrackerApp::createLoginContainer() {
    // Pass 'this' so the view can access the app and its managers
    root()->addNew<loginViewWidget>(this->environment(), this); 
}


void riskTrackerApp::handleLoginSuccess(const std::string& username) {
    // When login is successful, transition to the dashboard
    	userManager_->setCurrentUser(username);
	showDashboard();
}

void riskTrackerApp::showDashboard() {
    root()->clear();
    root()->addNew<navView>(this);
    
    // Here you would eventually load your Dashboard view widget, will be finished by View Team
    // root()->addNew<DashboardWidget>(this); 

    
}

void riskTrackerApp::logout() {
    userManager_->logout();
    root()->clear();
    createLoginContainer();
}

void riskTrackerApp::updateActivity() {
        lastActivity_=std::chrono::steady_clock::now();
}
