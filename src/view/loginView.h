#pragma once


// put in alphabetical
#include <Wt/WApplication.h> 
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPasswordEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WWidget.h> 

#include "loginModel.h" // Added back
#include "riskTrackerApp.h"

class loginViewWidget : public Wt::WContainerWidget
{
public:
    loginViewWidget() = delete;
    explicit loginViewWidget(const Wt::WEnvironment& env, riskTrackerApp* app);

private:
    riskTrackerApp* app;
//    loginModel model; // Added back

    Wt::WContainerWidget* loginCard;
    Wt::WText* title;
    Wt::WText* errorNotification;
    Wt::WLineEdit* userEdit;
    Wt::WPasswordEdit* passEdit;
    Wt::WPushButton* btn;

    void showError(const std::string& message);
    void hideError();
    void attemptLogin();
    
};
