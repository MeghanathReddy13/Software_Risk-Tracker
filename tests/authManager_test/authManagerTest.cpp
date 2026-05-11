/* Josh Nettle */
/* 4/28/2026 */
#include <gtest/gtest.h>
#include <memory>
#include "authManagerModel.h"
#include "databaseManagerModel.h"

class AuthenticatorTest : public ::testing::Test {
protected:
	std::shared_ptr<DatabaseManager> db;
	std::unique_ptr<Authenticator> auth;

	void SetUp() override {
		db = std::make_shared<DatabaseManager>();
		auth = std::make_unique<Authenticator>(db);
	}
};

TEST_F(AuthenticatorTest, VerifyUserSuccess) {
	std::string username = "testUser";
	std::string password = "SecretPassword123";

	User newUser;
	newUser.setUserName(username);
	newUser.setPassHash(auth->generateHash(password));
	db->addUser(newUser);

	EXPECT_TRUE(auth->verifyUser(username, password));
}

TEST_F(AuthenticatorTest, VerifyUserWrongPassword) {
	std::string username = "testUser";
	std::string realPassword = "correct_password";
	std::string wrongPassword = "wrong_password";

	User newUser;
	newUser.setUserName(username);
	newUser.setPassHash(auth->generateHash(realPassword));
	db->addUser(newUser);

	EXPECT_FALSE(auth->verifyUser(username, wrongPassword));
}

TEST_F(AuthenticatorTest, VerifyUserNotFound) {
	EXPECT_FALSE(auth->verifyUser("fake_user_99", "any_password"));
}

TEST_F(AuthenticatorTest, VerifyUserEmptyInput) {
	EXPECT_FALSE(auth->verifyUser("", "password"));
	EXPECT_FALSE(auth->verifyUser("username", ""));
	EXPECT_FALSE(auth->verifyUser("", ""));
}

TEST_F(AuthenticatorTest, GenerateHashIsConsistent) {
	std::string pass = "password123";
	std::string hash1 = auth->generateHash(pass);
	std::string hash2 = auth->generateHash(pass);

	EXPECT_EQ(hash1, hash2);
	EXPECT_NE(hash1, pass);
	EXPECT_EQ(hash1.length(), 64);
}
