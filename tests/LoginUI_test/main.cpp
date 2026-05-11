#include <gtest/gtest.h>
#include <Wt/Test/WTestEnvironment.h>
#include <Wt/WEvent.h>
#include "login.h"

class LoginUITest : public ::testing::Test {
protected:
    void SetUp() override {
        static Wt::Test::WTestEnvironment env; 
        app = std::make_unique<cs456Application>(env);
    }

    std::unique_ptr<cs456Application> app;

    // --- HELPER METHODS ---
    void clickLoginButton() {
        Wt::JavaScriptEvent jsEvent; 
        Wt::WMouseEvent mouseEvent(jsEvent); 
        app->loginButton->clicked().emit(mouseEvent);
    }

    bool isErrorVisible() { return app->errorNotification->isVisible(); }
    std::string getErrorText() { return app->errorNotification->text().toUTF8(); }
    
    //Allows the test to type into the private widgets
    void setCredentials(const std::string& user, const std::string& pass) {
        app->username->setText(user);
        app->password->setText(pass);
    }
};

// Test 1: Verify Empty Username fails
TEST_F(LoginUITest, RejectEmptyUsername) {
    // 1. Set empty username, valid password
    setCredentials("", "password123");

    // 2. Click Login
    clickLoginButton();

    // 3. Assert error
    EXPECT_TRUE(isErrorVisible());
    EXPECT_EQ(getErrorText(), "Username cannot be empty");
}

// Test 2: Verify Empty Password fails
TEST_F(LoginUITest, RejectEmptyPassword) {
    // 1. Set valid username, empty password
    setCredentials("ValidUser", "");

    // 2. Click Login
    clickLoginButton();

    // 3. Assert error
    EXPECT_TRUE(isErrorVisible());
    EXPECT_EQ(getErrorText(), "Password cannot be empty");
}

// Test 3: Verify Success
TEST_F(LoginUITest, AllowValidCredentials) {
    setCredentials("Hannah", "SecurePass");
    clickLoginButton();
    EXPECT_EQ(getErrorText(), "Login Successful");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
