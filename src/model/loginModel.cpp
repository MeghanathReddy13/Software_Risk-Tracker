/*
* Name: Nick Germann
* Project: Risk Tracker Application
* Module: Login Model section
* Description: This is the back end model for loging in and
* authorizing users.
*/

// loginModel.cpp


#include <string>

#include "loginModel.h"
#include "userManagerModel.h"
//#include <iostream>		// not needed for WT

// #include <Wt/WBreak.h>	// all below of needed for view not model
// #include <Wt/WLineEdit.h>
// #include <Wt/WPushButton.h>
// #include <Wt/WText.h>


// Made edits so that it not interacts with userManagerModel NG 04/04
loginModel::loginModel(std::shared_ptr<UserManager> userManager)
	: userManager(std::move(userManager))
{
	this->userManager = userManager;
        //User currentUser = ___->getUserByIdentity(user);
	//return (user == "admin" && pass == "admin");
}

bool loginModel::authorize(const std::string& user, const std::string& pass) const
{
	if(!userManager)
	{
		return false;
	}
	return userManager->login(user, pass);
}


	/*
		Below code is primarily visual, commenting out for integration.
	*/
	// addWidget(std::make_unique<Wt::WText>("<h1>Login</h1>"));
	// addWidget(std::make_unique<Wt::WText>("Username: "));
	// auto* userEdit = addWidget(std::make_unique<Wt::WLineEdit>());
	// userEdit->setPlaceholderText("username");

	// addWidget(std::make_unique<Wt::WBreak>());
	// addWidget(std::make_unique<Wt::WText>("Password: "));
	// auto* passEdit = addWidget(std::make_unique<Wt::WLineEdit>());

	// passEdit->setEchoMode(Wt::EchoMode::Password);
	// passEdit->setPlaceholderText("password");
	// addWidget(std::make_unique<Wt::WBreak>());

	// auto* btn = addWidget(std::make_unique<Wt::WPushButton>("Log in"));

	// auto* status = addWidget(std::make_unique<Wt::WText>("<p></p>"));

	// btn->clicked().connect([=] {
	// 		const auto u = userEdit->text().toUTF8();
	// 		const auto p = passEdit->text().toUTF8();
	// 		std::cout << "Login attempt user=" << u << " pass=" << p <<
	// 		"\n";

	// 		if (u== "admin" && p == "admin") {
	// 		status->setText("<p><b>Success!</b> Welcome. </p>");
	// 		} else {
	// 			status->setText("<p><b>Denied.</b> Try admin/admin.</p>");
	// 			}
	// 		});
    
