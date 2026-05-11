#pragma once

#include <memory>
#include <string>

#include <Wt/WContainerWidget.h>

class UserManager;

class loginModel 
{
    public:
        loginModel() = delete;
        explicit loginModel(std::shared_ptr<UserManager> userManager);    
	bool authorize(const std::string &user, const std::string &pass) const;

    private:
        std::shared_ptr<UserManager> userManager;
};

