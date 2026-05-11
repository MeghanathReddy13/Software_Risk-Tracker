/* Alli */
/* 3/14/2026 */
#ifndef ACCESS_H
#define ACCESS_H

#include <Wt/Dbo/Dbo.h>

#include "projectModel.h"
#include "userModel.h"

namespace dbo = Wt::Dbo;

class Access : public dbo::Dbo<Access>{
    private:
        dbo::ptr<User>      user;
        dbo::ptr<Project>   project;

    public:
        template<class Action>
        void persist(Action& a)
        {
                dbo::belongsTo(a, user, "user");
                dbo::belongsTo(a, project, "project");
        }

        //Constructors 
        Access() = default; //delete;
        Access(dbo::ptr<User> u, dbo::ptr<Project> p) : user(u), project(p) {
            }

        //Getters
        dbo::ptr<User> getUser() const {
                return user;
        }
        dbo::ptr<Project> getProject() const {
                return project;
        }

        //Setters
        void setUser(dbo::ptr<User> u) {
                user = u;
        }
        void setProject(dbo::ptr<Project> p) {
                project = p;
        }
};

#endif // ACCESS_H
