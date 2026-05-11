/* Brandon Zuniga */
/* 3/1/2026 */
#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "userModel.h" // Replaced the struct with the new class header
#include "databaseManagerModel.h"

// Forward declaration of the Authenticator class per the SDD
class Authenticator;
class DatabaseManager;

class UserManager {
public:
    // Added Authenticator dependency
    UserManager(std::shared_ptr<DatabaseManager> dbManager, std::shared_ptr<Authenticator> auth);
//to integrate create user    
   void setCurrentUser(const std::string& username);
 
    bool login(const std::string& username, const std::string& password);
    void logout();
    
    bool isLoggedIn() const;
    User getCurrentUser() const;
    
    bool createUser(const std::string& name, const std::string& username, const std::string& password, const std::string& role);
    bool deleteUser(int userId);
    bool editUser(int userId, const std::string& newName,const std::string& newEmail, const std::string& newPassword, const std::string& newRole);
    void idleTimer(); //  Renamed from checkInactivityTimeout to match SDD
    
    bool isAdmin() const;
    void setOnActivity(std::function<void()> callback) {
        onActivity = callback;
    }

private:
    std::shared_ptr<DatabaseManager> dbManager_;
    std::shared_ptr<Authenticator> auth_; // Added for proper auth component integration
    User currentUser_;
    bool loggedIn_;
    std::function<void()> onActivity;
    
};

#endif // USER_MANAGER_H
