/* Brandon Zuniga */
/* 3/1/2026 */
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <Wt/WServer.h>
#include <Wt/WLogger.h>
#include <Wt/Dbo/Dbo.h>

namespace dbo = Wt::Dbo;

class User : public dbo::Dbo<User>{
public:  
    //enum UserRole { ADMIN=0, USER=1 };
private:
    // Attributes mapped directly from the SDD
    int                         userID;
    std::string                 name;
    std::string                 userName;
    std::string                 passHash;
    std::vector<std::string>    roles;;
    std::vector<std::string>    projects;
    Wt::WServer*                active; 
    std::string                 lastAction;
    //There is no entry method in WLogger
    //Wt::WLogger::Entry          lastAction; 

public:
    template<class Action>
        void persist(Action& a)
        {
            dbo::field(a, name,     "name");
            dbo::field(a, userName,    "userName");
            dbo::field(a, passHash, "passHash");
        }

    // Constructor initializes defaults
    User() : userID(-1), active(nullptr) {}

    // Getters
    int getID() const { 
		return userID; 
	}
    std::string getName() const { 
		return name; 
	}
    std::string getUserName() const { 
		return userName; 
	}
    std::string getPassHash() const { 
		return passHash; 
	}
    std::vector<std::string>  getRole() const {
                return roles;
        }
    std::vector<std::string> getProjects() const { 
		return projects; 
	}
    Wt::WServer* getActive() const { 
		return active; 
	}
   //Wt::WLogger::Entry getLastAction() {
    std::string getLastAction() {
                return lastAction;
    }
        

    // Setters
    void setID(int id) { 
		userID = id; 
	}
    void setName(const std::string& newName) { 
		name = newName; 
	}
    void setUserName(const std::string& newUserName) { 
		userName = newUserName; 
	}
    void setPassHash(const std::string& newPassHash) { 
		passHash = newPassHash; 
	}
    void setRole(const std::vector<std::string>& newRoles) { 
		roles = newRoles; 
	}
    void setProjects(const std::vector<std::string>& newProjects) { 
		projects = newProjects; 
	}
    void setActive(Wt::WServer* newActive) { 
		active = newActive; 
	}
    void setLastAction(const std::string& newLastAction) {//Wt::WLogger::Entry& newLastAction) { 
		lastAction = newLastAction; 
	}
};

#endif // USER_H
