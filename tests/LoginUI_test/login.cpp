#include "login.h"

cs456Application::cs456Application(const Wt::WEnvironment& env) : Wt::WApplication(env) {
    setTitle("Login Software Risk Tracker");
    
    loginCard = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    errorNotification = loginCard->addWidget(std::make_unique<Wt::WText>(""));
    errorNotification->hide();
    
    username = loginCard->addWidget(std::make_unique<Wt::WLineEdit>());
    password = loginCard->addWidget(std::make_unique<Wt::WPasswordEdit>());
    loginButton = loginCard->addWidget(std::make_unique<Wt::WPushButton>("Login"));

    loginButton->clicked().connect([this] {
        std::string userText = username->text().toUTF8();
    	std::string passText = password->text().toUTF8();

    	logicModel.attemptLogin(userText, passText); 
        showError(logicModel.getStatus());
    });
}

void cs456Application::showError(const std::string& message) {
    errorNotification->setText(message);
    errorNotification->show();
}
