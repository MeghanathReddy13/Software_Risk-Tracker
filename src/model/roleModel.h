/* Alli */
/* 3/14/2026 */
#ifndef ROLE_H
#define ROLE_H

#include <string>
#include <Wt/Dbo/Dbo.h>

#include "userModel.h"

namespace dbo = Wt::Dbo;

class Role : public dbo::Dbo<Role> {
    private: 
        dbo::ptr<User>  user;
        std::string     roleTitle;

    public:
        template<class Action>
        void persist(Action& a)
{
            dbo::belongsTo(a, user, "user");
            dbo::field(a, roleTitle, "roleTitle");
        }
        
        //Constructors
        Role() = default; //delete;
        Role(dbo::ptr<User> u, std::string rt) : user(u), roleTitle(rt) {
        }

        //Getters
        dbo::ptr<User> getUser() const {
                return user;
        }
        std::string getRoleTitle() const {
                return roleTitle;
        }

        //Setters
        void setUser(dbo::ptr<User> u) {
                user = u;
        }
        void setRoleTitle(const std::string& rt) {
                roleTitle = rt;
        }
};

#endif //ROLE_H

