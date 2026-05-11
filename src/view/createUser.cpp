#include "createUser.h"
#include "riskTrackerApp.h"
#include "userManagerModel.h"

#include <Wt/WApplication.h>

CreateUserForm::CreateUserForm()
{
    addStyleClass("create-user-page");
    buildForm();
	
}

void CreateUserForm::buildForm()
{
    // Title
    auto title = addWidget(std::make_unique<Wt::WText>("Create User"));
    title->addStyleClass("create-user-title");

    // Subtitle
    auto subtitle = addWidget(std::make_unique<Wt::WText>("Add new user"));
    subtitle->addStyleClass("create-user-subtitle");

    // Error message
    errorMessage = addWidget(std::make_unique<Wt::WText>(""));
    errorMessage->addStyleClass("create-user-error");
    errorMessage->hide();

    // Form container
    auto formContainer = addWidget(std::make_unique<Wt::WContainerWidget>());
    formContainer->addStyleClass("create-user-form");

    // Full Name
    auto nameLabel = formContainer->addWidget(std::make_unique<Wt::WText>("Full Name"));
	nameLabel->addStyleClass("form-label");
    fullName = formContainer->addWidget(std::make_unique<Wt::WLineEdit>());

	fullName->setPlaceholderText("Enter full name");
	fullName->addStyleClass("form-input");

    // Email
	auto emailLabel = formContainer->addWidget(std::make_unique<Wt::WText>("Email"));
	emailLabel->addStyleClass("form-label");
    email = formContainer->addWidget(std::make_unique<Wt::WLineEdit>());
	email->setPlaceholderText("Enter email address");
	email->addStyleClass("form-input");

    // Password
    auto passLabel = formContainer->addWidget(std::make_unique<Wt::WText>("Password"));
	passLabel->addStyleClass("form-label");
    password = formContainer->addWidget(std::make_unique<Wt::WPasswordEdit>());
	password->setPlaceholderText("Enter password");
	password-> addStyleClass("form-input");

    // Confirm Password
	auto confirmLabel = formContainer->addWidget(std::make_unique<Wt::WText>("Confirm Password"));
	confirmLabel->addStyleClass("form-label");
    confirmPassword = formContainer->addWidget(std::make_unique<Wt::WPasswordEdit>());
	confirmPassword->setPlaceholderText("confirm password");
	confirmPassword->addStyleClass("form-input");

    // Role
	auto roleLabel =  formContainer->addWidget(std::make_unique<Wt::WText>("Role"));
	roleLabel->addStyleClass("form-label");
    role = formContainer->addWidget(std::make_unique<Wt::WComboBox>());
    role->addItem("-- Select Role --");
    role->addItem("Admin");
    role->addItem("User");
	role->addStyleClass("form-input");

	auto submit = formContainer->addWidget(std::make_unique<Wt::WPushButton>("Create User"));
	submit->addStyleClass("create-user-btn");

	submit->clicked().connect([this](){
	handleCreate();
});
}
void CreateUserForm::handleCreate()
{
    // Clear previous error
    errorMessage->hide();
	auto trim = [](std::string s){
		s.erase(0,  s.find_first_not_of(" \n\r\t"));
		s.erase(s.find_last_not_of("\n\r\t") + 1);
		return s;
	};
    std::string name = fullName->text().toUTF8();
    std::string mail = email->text().toUTF8();
    std::string pass = password->text().toUTF8();
    std::string confirm = confirmPassword->text().toUTF8();
    int roleIndex = role->currentIndex();

	name = trim(name);
	mail=trim(mail);
	pass = trim (pass);
	confirm = trim(confirm);
    if (name.empty() || mail.empty() || pass.empty() || confirm.empty()) {
        errorMessage->setText("All fields are required.");
        errorMessage->show();
        return;
    }

    if (pass != confirm) {
        errorMessage->setText("Passwords do not match.");
        errorMessage->show();
        return;
    }

    if (roleIndex == 0) {
        errorMessage->setText("Please select a role.");
        errorMessage->show();
        return;
    }

	std::string roleStr = (roleIndex ==1) ? "admin" : "user";
	
	auto app = static_cast<riskTrackerApp*>(Wt::WApplication::instance());
	if(!app){
		errorMessage->setText("App nit available");
		errorMessage->show();
		return;
	}
	bool success = app->getUserManager()->createUser(name, mail, pass, roleStr);
		if(!success){
			errorMessage->setText("Failed to create user.");
			errorMessage->show();
			return;
		}
		
	if(onUserCreated){
		onUserCreated(name, mail, pass, roleStr);
	}

	fullName->setText("");
	email->setText("");
	password->setText("");
	confirmPassword->setText("");
	role->setCurrentIndex(0);
	
	errorMessage->setText("User created Successfully!");
	errorMessage->show();
}
