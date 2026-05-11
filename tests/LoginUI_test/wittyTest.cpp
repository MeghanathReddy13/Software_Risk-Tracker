#include "wittyTest.h"

namespace witty {
    WittyTest::WittyTest() : status_("") {}

    void WittyTest::attemptLogin(const std::string& username, const std::string& password) {
        if (username.empty()) {
            status_ = "Username cannot be empty";
        } 
        else if (password.empty()) {
            status_ = "Password cannot be empty";
        } 
        else {
            status_ = "Login Successful";
        }
    }

    std::string WittyTest::getStatus() const {
        return status_;
    }
}
