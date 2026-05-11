#ifndef LOGIN_H
#define LOGIN_H

#include <Wt/WApplication.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPasswordEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBreak.h>
#include "wittyTest.h"

class LoginUITest; // Forward declaration for GTest

class cs456Application : public Wt::WApplication {
public:
    cs456Application() = delete;
    explicit cs456Application(const Wt::WEnvironment& env);
    
    // Testing "Backdoor"
    friend class LoginUITest;

private:
    witty::WittyTest logicModel;
    
    Wt::WContainerWidget* loginCard;
    Wt::WText* errorNotification;
    Wt::WLineEdit* username;
    Wt::WPasswordEdit* password;
    Wt::WPushButton* loginButton;

    void showError(const std::string& message);
};

#endif
