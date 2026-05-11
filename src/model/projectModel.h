/* Brandon Zuniga */
/* 3/08/2026 */
#ifndef PROJECT_MODEL_H
#define PROJECT_MODEL_H

#include <string>
#include <vector>
#include <Wt/Dbo/Dbo.h>
#include <chrono> //#include <Wt/WDateTime.h> 
#include "riskItemModel.h"

namespace dbo = Wt::Dbo;

class Project : public dbo::Dbo<Project> {
private:
    int projectIdLocal; 
    std::string name; 
    int impactCount; // Added per SSD 
    int probCount; 
    std::chrono::system_clock::time_point created;   //changed to chrono
    std::chrono::system_clock::time_point modified;  //changed to chrono
    std::vector<std::string> users; 
    std::vector<std::string> admins; 
    std::vector<RiskItem> risks; 

public:
    template<class Action>
    void persist(Action& a)
    {
	    dbo::field(a, name, "name");
	    dbo::field(a, impactCount, "impactCount");
	    dbo::field(a, probCount, "probCount");
	    dbo::field(a, created, "created");
	    dbo::field(a, modified, "modified");
    }

    // Constructor initializes safe defaults
    Project() : projectIdLocal(-1), impactCount(5), probCount(5) {
    }

    // Getters
    int getID() const { 
        return projectIdLocal; 
    }
    std::string getName() const { 
        return name; 
    }
    int getImpactCount() const { 
        return impactCount; 
    }
    int getProbCount() const { 
        return probCount; 
    }
    std::chrono::system_clock::time_point getCreated() const {
	    return created;
    }
    std::chrono::system_clock::time_point getModified() const {
	    return modified;
    }
    std::vector<std::string> getUsers() const { 
        return users; 
    }
    std::vector<std::string> getAdmins() const { 
        return admins; 
    }
    std::vector<RiskItem> getRisks() const { 
        return risks; 
    }

    // Setters
    void setID(int id) { 
        projectIdLocal = id; 
    }
    void setName(const std::string& n) { 
        name = n; 
    }
    void setImpactCount(int count) { 
        impactCount = count; 
    }
    void setProbCount(int count) { 
        probCount = count; 
    }
    void setCreated(std::chrono::system_clock::time_point c) {
	created = c;
    }
    void setModified(std::chrono::system_clock::time_point m) {
	modified = m;
    }
    void setUsers(const std::vector<std::string>& u) { 
        users = u; 
    }
    void setAdmins(const std::vector<std::string>& a) { 
        admins = a; 
    }
    void setRisks(const std::vector<RiskItem>& r) { 
        risks = r; 
    }
};

#endif // PROJECT_MODEL_H
