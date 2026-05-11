/* Alli */
/* 03-19-2026 */

#include "authManagerModel.h"
#include "databaseManagerModel.h"
#include <cstdio>
#include <string>
#include <openssl/sha.h>

// Constructor
Authenticator::Authenticator(std::shared_ptr<DatabaseManager> dbManager)
    : dbManager_(dbManager)
{
}

bool Authenticator::verifyUser(const std::string& username, const std::string& password)
{
	std::cout<< "LOGIN ATTEMPT\n";
	std::cout<<"USERNAME: " << username << std::endl;
	std::cout << "INPUT PASSWORD: " << password << std::endl;
    if (username.empty() || password.empty()) {
        return false;
    }

    User user = dbManager_->getUserByIdentity(username);
    std::cout<< "FOUND USER ID: " << user.getID()<< std::endl;
	std::cout << "found username: " << user.getUserName()<< std::endl;

	if (user.getID() < 0) {
        return false;
    }
	std::string generated = generateHash(password);
	std::string stored = user.getPassHash();

	std::cout << "GENERATED HASH: " << generateHash(password) << std::endl;
	std::cout << "Stored Hash: " << user.getPassHash()<< std::endl;
    return generated == stored;
}

std::string Authenticator::generateHash(const std::string& password) {
    // very simple SHA256 example
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), hash);

    std::string hex;
    char buf[3];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        snprintf(buf, sizeof(buf), "%02x", hash[i]);
        hex += buf;
    }
    return hex;
}
