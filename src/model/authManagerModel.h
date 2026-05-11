#pragma once

#include <string>
#include <memory>

// Forward declaration
class DatabaseManager;

class Authenticator {
public:
    // Constructor (accept DB if you want later)
    explicit Authenticator(std::shared_ptr<DatabaseManager> dbManager);

    // Basic authentication function
    bool verifyUser(const std::string& username, const std::string& password);
    std::string generateHash(const std::string& password);

private:
    std::shared_ptr<DatabaseManager> dbManager_;
};
