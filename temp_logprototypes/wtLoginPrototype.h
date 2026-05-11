// "Wt Login Prototype #1"
#include <Wt/Auth/Login.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/AbstractUserDatabase.h>
#include <string>

class Login {
public:
    Login(Wt::Auth::AbstractUserDatabase& users, Wt::Auth::PasswordService& passwordService) : users_(users), passwordService_(passwordService) {
	}

    bool login(const std::string& username, const std::string& password) {
        Wt::Auth::User user = users_.findWithPassword(username, password);

        if (user.isValid()) {
            wtLoginState_.login(user);
            return true;
        }
        
        return false;
    }

    void logout() {
        wtLoginState_.logout();
    }

    bool isLoggedIn() const {
        return wtLoginState_.loggedIn();
    }

    Wt::Auth::User currentUser() const {
        return wtLoginState_.user();
    }

private:
    Wt::Auth::Login wtLoginState_;
    Wt::Auth::AbstractUserDatabase& users_;
    Wt::Auth::PasswordService& passwordService_;
};
