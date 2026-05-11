/* Brandon Zuniga */
/* Revised 4/5/2026 */
#include "userManagerModel.h"
#include "authManagerModel.h"
#include <iostream>
#include <cctype>
#include <algorithm>
#include <Wt/WTime.h>
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WDateTime.h>
#include <chrono>

UserManager::UserManager(std::shared_ptr<DatabaseManager> dbManager, std::shared_ptr<Authenticator> auth) 
    : dbManager_(dbManager), auth_(auth), loggedIn_(false) {
    currentUser_.setID(-1); 
}


bool UserManager::login(const std::string& username, const std::string& password) {
    if (username.empty() || password.empty()) {
        return false;
    }

    Wt::WDateTime now = Wt::WDateTime::currentDateTime();
    auto tp = std::chrono::system_clock::from_time_t(now.toTime_t());
    
    // Delegate password hashing and verification to the Authenticator 
    if (auth_->verifyUser(username, password)) { 
        // Fetch the populated User object from DB upon valid credentials
        currentUser_ = dbManager_->getUserByIdentity(username);

        for (const auto& r : currentUser_.getRole()) {
            std::cout << "LOGIN ROLE: [" << r << "]\n";
        }

	std::cout <<"ROLES AFTER LOGIN: \n";
	for(const auto&r :currentUser_.getRole()){
		std::cout << "[" << r << "]\n";
	} 
        loggedIn_ = true;
        
        // Execute logActivity with Wt::WTime and required SDD parameters 
        //Wt::WDateTime now = Wt::WDateTime::currentDateTime();
        //auto tp = std::chrono::system_clock::from_time_t(now.toTime_t());
        dbManager_->logActivity(
            //Wt::WTime::currentTime(), 
            tp,
            currentUser_.getUserName(), 
            "LOGIN", 
            "Authentication", 
            "Success"
        );
        if (onActivity) {
                onActivity();
        }
        return true;
    } else {
        // Log the failed attempt
        dbManager_->logActivity(
            //Wt::WTime::currentTime(), 
            tp,
            username, 
            "LOGIN_FAIL", 
            "Authentication", 
            "Invalid Credentials"
        );
        return false;
    }
}

void UserManager::logout() {
    if (loggedIn_) {
        // Reset state using setters
        currentUser_ = User(); 
        currentUser_.setID(-1);
        loggedIn_ = false;
    }
}

bool UserManager::createUser(const std::string& name, const std::string& username, const std::string& password, const std::string& role) {
        
	std::cout << "Is Admin? " << isAdmin() << std::endl;
	std::cout << "Current user: " << currentUser_.getUserName() << std:: endl;  
	std::cout << "password recieved in create : [" << password<<"]\n";
	 if (!isAdmin()) {
       	 return false;
    	  }
	
	// Securely hash the password using the Authenticator
    std::string secureHash = auth_->generateHash(password);
	std::cout << "HASH STORED: " << secureHash << std::endl;
    // Populate the new User object
    User newUser;
    newUser.setName(name);
    newUser.setUserName(username);
    newUser.setPassHash(secureHash);
    
    std::vector<std::string> roles = {role};
    newUser.setRole(roles);

    int newId = dbManager_->addUser(newUser);
    bool success = newId > 0;
    
    // Log the creation
    Wt::WDateTime now = Wt::WDateTime::currentDateTime();
    auto tp = std::chrono::system_clock::from_time_t(now.toTime_t());

    if (success) {
        dbManager_->logActivity(
            //Wt::WTime::currentTime(), 
            tp,
            currentUser_.getUserName(), 
            "CREATE_USER", 
            "User Admin", 
            "Created user: " + username
        );
    }

    return success;
}

bool UserManager::deleteUser(int userId) {
	std::cout<<"IS ADMIN?" <<isAdmin()<<std::endl;
    if (!isAdmin()) {
        return false;
    }
    return dbManager_->deleteUser(userId) == 1;
}

bool UserManager::editUser(int userId, const std::string& newName,const std::string& newEmail, const std::string& newPassword,  const std::string& newRole) {
	std::cout<<"IS ADMIN?" <<isAdmin()<<std::endl;
    if (!isAdmin()) {
        return false;
    }

	User updated;
    updated.setID(userId);
	if(!newName.empty())
    		updated.setName(newName);
	if(!newEmail.empty())
    		updated.setUserName(newEmail);
	if(!newPassword.empty()){
		std::string hash = auth_->generateHash(newPassword);
    		updated.setPassHash(hash);
	}
	if(!newRole.empty())
    		updated.setRole({newRole});

    return dbManager_->editUser(updated) != -1;
}

//sets user to their identity
void UserManager::setCurrentUser(const std::string& username){
	currentUser_=dbManager_->getUserByIdentity(username);
}

bool UserManager::isAdmin() const {
    if (!loggedIn_) return false;
    
    // Check using the getter for the roles vector
    for (auto role : currentUser_.getRole()) {
	role.erase(std::remove_if(role.begin(), role.end(),[](unsigned char c){ return::isspace(c);}), role.end());
	std:: transform(role.begin(), role.end(), role.begin(),[](unsigned char c) { return std::tolower(c);});
	std::cout << " CHECKING ROLE: [" <<role<<"]\n";

        if (role == "admin") {
            return true;
        }
    }
    return false;
}

void UserManager::idleTimer() {
    // If the user isn't logged in, there is nothing to time out
    if (!loggedIn_) {
        return;
    }

    // Ensure we are inside an active Wt session
    if (Wt::WApplication::instance()) {
        
        // Wt automatically tracks how long the user has been idle in seconds
        int idleSeconds = 0;//Wt::WApplication::instance()->environment().idleTime();
        
        // SAFE-2 Requirement: 15 minutes 
        int timeoutLimitSeconds = 15 * 60; 

        if (idleSeconds >= timeoutLimitSeconds) {
            Wt::WDateTime now = Wt::WDateTime::currentDateTime();
            auto tp = std::chrono::system_clock::from_time_t(now.toTime_t());           
            // Log the specific timeout event matching the SDD
            dbManager_->logActivity(
                //Wt::WTime::currentTime(), 
                tp,
                currentUser_.getUserName(), 
                "TIMEOUT", 
                "User Administration", 
                "Logged out due to inactivity. Log back in."
            );
            
            // Call your existing logout function to reset the state
            logout(); 
        }
    }
}

User UserManager::getCurrentUser() const {
    return currentUser_;
}

bool UserManager::isLoggedIn() const {
    return loggedIn_;
}

