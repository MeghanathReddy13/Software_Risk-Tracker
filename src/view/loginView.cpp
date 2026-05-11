/* Revised 4/5/2026 */
/* Revised by Brandon Zuniga */
/* UI for the Login page of the risk tracker */

#include "loginView.h"
#include "riskTrackerApp.h"
#include "userManagerModel.h"

// 02/19/2026
// Nick G (changes for integration)
// changed loginView to loginViewWidget
// Our current code being worked on individually has been coded to run by itself
// needs to have the top application/environment classes changed to widgets.
// login should be widget and not environment
// https://www.webtoolkit.eu/wt/doc/reference/html/classWt_1_1WWidget.html
// https://www.webtoolkit.eu/wt/doc/reference/html/classWt_1_1WContainerWidget.html
loginViewWidget::loginViewWidget(
    const Wt::WEnvironment&, riskTrackerApp* app):
    Wt::WContainerWidget(), app(app)
{
    // Convert application to application instance
    // https://www.webtoolkit.eu/wt/doc/reference/html/classWt_1_1WApplication.html
    // Set title and link the CSS
    //auto* application = Wt::WApplication::instance() //NG tried for continuity
            // doesn't seem to be needed.
    //setTitle("Login Software Risk Tracker");
    //application->setTitle("Risk Tracker");
    //useStyleSheet("login.css");
    // no longer needed as single style sheet in riskTrackerApp.

    // created the card
    // card is now just part of the instance
    loginCard = addWidget(std::make_unique<Wt::WContainerWidget>());
    loginCard->addStyleClass("login-card");

    title = loginCard->addWidget(std::make_unique<Wt::WText>("Risk Tracker"));
    title->addStyleClass("login-title");

    loginCard->addWidget(std::make_unique<Wt::WBreak>());

    loginCard->addWidget(std::make_unique<Wt::WText>("Username"));
    userEdit = loginCard->addWidget(std::make_unique<Wt::WLineEdit>());
    // added enter btn 4/4 NG
    userEdit->enterPressed().connect(this, &loginViewWidget::attemptLogin);

    loginCard->addWidget(std::make_unique<Wt::WText>("Password"));
    passEdit = loginCard->addWidget(std::make_unique<Wt::WPasswordEdit>());
    // added enter btn 4/4 NG
    passEdit->enterPressed().connect(this, &loginViewWidget::attemptLogin);

    btn = loginCard->addWidget(std::make_unique<Wt::WPushButton>("Login"));
    btn->clicked().connect(this, &loginViewWidget::attemptLogin);

    errorNotification = addWidget(std::make_unique<Wt::WText>(""));
    errorNotification->hide();
}


void
loginViewWidget::attemptLogin()
{
	auto trim = [](std::string s){
		s.erase(0, s.find_first_not_of("\n\r\t"));
		s.erase(s.find_last_not_of("\n\r\t") +1);
		return s;
	};
    const std::string u = trim(userEdit->text().toUTF8());
    const std::string p = trim(passEdit->text().toUTF8());

    
    if (!app) return;
	auto userManager = app->getUserManager();
        if (userManager && userManager->login(u,p)){
            // In risk tracker app to handle authorization.
            // Notes for handling authorization will be in there once 
            // understood better. NG
            app->handleLoginSuccess(u);
    } else {
        errorNotification->setText("Invalid Username or Password.");
        errorNotification->show();
    }
}
/*   if (!app) {
        return;
    }
    std::shared_ptr<UserManager> userManager = app->getUserManager();
    if (userManager && userManager->login(u, p)) {
        app->handleLoginSuccess(u);
        return;
    }
    errorNotification->setText("Invalid username or password.");
    errorNotification->show();
}
*/

// Invalid credentials message added
void
loginViewWidget::showError(const std::string& message)
{
    errorNotification->setText(message);
    errorNotification->show();
}

void
loginViewWidget::hideError()
{
    errorNotification->hide();
}

// Nick's Notes for Integration:
//     // Marker for code scrolling
//     // Logans Code, worked but needed conversion to widget to run with everything else.
//     loginCard = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
//     loginCard->addStyleClass("login-card");

//     // title for the card
//     title = loginCard->addWidget(
//         std::make_unique<Wt::WText>("Software Risk Tracker"));
//     title->addStyleClass("login-title");

//     loginCard->addWidget(std::make_unique<Wt::WBreak>());

//     // error notification
//     errorNotification = loginCard->addWidget(
// 		   std::make_unique<Wt::WText>("Invalid Credentials!"));
//     errorNotification->addStyleClass("error-notification");
//     errorNotification->hide();
    
//     loginCard->addWidget(std::make_unique<Wt::WBreak>());

//     // user and password inputs
//     loginCard->addWidget(std::make_unique<Wt::WText>("Username"));
//     userEdit = loginCard->addWidget(std::make_unique<Wt::WLineEdit>());

//     loginCard->addWidget(std::make_unique<Wt::WText>("Password"));
//     passEdit = loginCard->addWidget(std::make_unique<Wt::WPasswordEdit>());

//     // Login button
//     btn = loginCard->addWidget(
//         std::make_unique<Wt::WPushButton>("Login"));
  

//     // connect button click to show error
//     btn->clicked().connect([this] {
// 		   showError("Invalid Credentials!");
// 		   }); 
// }

// void loginViewWidget::showError(const std::string& message)
// {
// 	errorNotification->setText(message);
// 	errorNotification->show();
// }

// void loginViewWidget::hideError()
// {
// 	errorNotification->hide();
// }
