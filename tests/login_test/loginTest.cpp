/* Josh Nettle */
/* 05/03/2026 */
#include <gtest/gtest.h>
#include "loginModel.h"
#include "userManagerModel.h"
#include "databaseManagerModel.h"
#include "databaseModel.h"
#include "authManagerModel.h"

class LoginModelTest : public ::testing::Test {
protected: 
	std::shared_ptr<DatabaseManager> dbMgr;
	std::unique_ptr<loginModel> login;
	std::shared_ptr<UserManager> userMgr;
	std::shared_ptr<Authenticator> auth;

	void SetUp() override {
		Database& db = Database::instance(":memory:");

		dbMgr = std::make_shared<DatabaseManager>();
		auth = std::make_shared<Authenticator>(dbMgr);
		userMgr = std::make_shared<UserManager>(dbMgr, auth);
		login = std::make_unique<loginModel>(userMgr);
	
		{
		Wt::Dbo::Transaction t(db.session());
		User testAdmin;
		testAdmin.setName("Admin User");
		testAdmin.setUserName("admin");
		
		std::string hashedPw = auth->generateHash("admin");
		testAdmin.setPassHash(hashedPw);

		testAdmin.setRole({"admin"});
		
		dbMgr->addUser(testAdmin);

		}
	}	
};

TEST_F(LoginModelTest, AuthorizeSuccess) { 
	EXPECT_TRUE(login->authorize("admin", "admin"));
}

TEST_F(LoginModelTest, AuthorizeWrongUser) {
	EXPECT_FALSE(login->authorize("wrongUser", "admin"));
}

TEST_F(LoginModelTest, AuthorizeWrongPass) {
	EXPECT_FALSE(login->authorize("admin", "wrongPass"));
}

TEST_F(LoginModelTest, AuthorizeEmptyFields) {
	EXPECT_FALSE(login->authorize("",""));
}
