#pragma once

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WPasswordEdit.h>
#include <functional>
#include <string>
class CreateUserForm : public Wt::WContainerWidget
{
public:
    CreateUserForm();
    std::function<void(std::string, std::string,std::string, std::string)> onUserCreated;

private:
    Wt::WLineEdit* fullName;
    Wt::WLineEdit* email;
    Wt::WPasswordEdit* password;
    Wt::WPasswordEdit* confirmPassword;
    Wt::WComboBox* role;
//    Wt::WPushButton* createButton;
    Wt::WText* errorMessage;

    void buildForm();
    void handleCreate();
};
 
