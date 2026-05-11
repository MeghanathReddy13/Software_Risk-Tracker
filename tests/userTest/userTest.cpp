/*
 * Shelby Stanly
 * User Tests
 * 4/8/2026
 */

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include <Wt/WServer.h>

#include "userModel.h"
#include "userManagerModel.h"
#include "databaseManagerModel.h"
#include "authManagerModel.h"
#include "databaseModel.h"

namespace {
// ==========
// User tests
// ==========
class UserTest : public ::testing::Test {
    protected:
        User user;
};

TEST_F(UserTest, InitializingExpectedValues) {
    EXPECT_EQ(user.getID(), -1);
    EXPECT_EQ(user.getName(), "");
    EXPECT_EQ(user.getUserName(), "");
    EXPECT_EQ(user.getPassHash(), "");
    EXPECT_TRUE(user.getRole().empty());
    EXPECT_TRUE(user.getProjects().empty());
    EXPECT_EQ(user.getActive(), nullptr);
    EXPECT_EQ(user.getLastAction(), "");
}

TEST_F(UserTest, SetAndGetID) {
    user.setID(6969);
    EXPECT_EQ(user.getID(), 6969);
}

TEST_F(UserTest, SetAndGetName) {
    user.setName("Peter Parker");
    EXPECT_EQ(user.getName(), "Peter Parker");
}

TEST_F(UserTest, SetAndGetUserName) {
    user.setUserName("spiderman");
    EXPECT_EQ(user.getUserName(), "spiderman");
}

TEST_F(UserTest, SetAndGetPassHash) {
    user.setPassHash("webslinger");
    EXPECT_EQ(user.getPassHash(), "webslinger");
}

TEST_F(UserTest, SetAndGetRole) {
    std::vector<std::string> roles = {"Admin", "User"};
    user.setRole(roles);

    ASSERT_EQ(user.getRole().size(), 2);
    EXPECT_EQ(user.getRole()[0], "Admin");
    EXPECT_EQ(user.getRole()[1], "User");
}

TEST_F(UserTest, SetAndGetProjects) {
    std::vector<std::string> projects = {"ProjectRiskTracker", "ProjectRaspberry"};
    user.setProjects(projects);

    ASSERT_EQ(user.getProjects().size(), 2);
    EXPECT_EQ(user.getProjects()[0], "ProjectRiskTracker");
    EXPECT_EQ(user.getProjects()[1], "ProjectRaspberry");
}

TEST_F(UserTest, SetAndGetLastAction) {
    user.setLastAction("Login");
    EXPECT_EQ(user.getLastAction(), "Login");
}

// =================
// UserManager tests
// =================
class UserManagerTest : public ::testing::Test {
protected:
    std::shared_ptr<DatabaseManager> dbManager;
    std::shared_ptr<Authenticator> auth;
    std::unique_ptr<UserManager> userManager;

    void SetUp() override {
        Database::instance("test.db");

        dbManager = std::make_shared<DatabaseManager>();
        auth = std::make_shared<Authenticator>(dbManager);
        userManager = std::make_unique<UserManager>(dbManager, auth);
    }
};

TEST_F(UserManagerTest, LoggedOutFirst) {
    EXPECT_FALSE(userManager->isLoggedIn());
    EXPECT_EQ(userManager->getCurrentUser().getID(), -1);
}

TEST_F(UserManagerTest, AdminFalseWhenLoggedOut) {
    EXPECT_FALSE(userManager->isAdmin());
}

TEST_F(UserManagerTest, EmptyUsernameLoginFail) {
    EXPECT_FALSE(userManager->login("", "password"));
    EXPECT_FALSE(userManager->isLoggedIn());
}

TEST_F(UserManagerTest, EmptyPasswordLoginFail) {
    EXPECT_FALSE(userManager->login("username", ""));
    EXPECT_FALSE(userManager->isLoggedIn());
}

TEST_F(UserManagerTest, LogoutWhenLoggedOut) {
    EXPECT_NO_THROW({
        userManager->logout();
    });

    EXPECT_FALSE(userManager->isLoggedIn());
    EXPECT_EQ(userManager->getCurrentUser().getID(), -1);
}

TEST_F(UserManagerTest, IdleTimerDoesNothingIfLoggedOut) {
    EXPECT_NO_THROW({
        userManager->idleTimer();
    });

    EXPECT_FALSE(userManager->isLoggedIn());
    EXPECT_EQ(userManager->getCurrentUser().getID(), -1);
}

} // namespace
