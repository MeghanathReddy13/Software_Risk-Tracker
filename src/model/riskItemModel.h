/* Brandon Zuniga */
/* 2/22/2026 */
#ifndef RISKITEM_H
#define RISKITEM_H

#include <string>
#include <Wt/Dbo/Dbo.h>

namespace dbo = Wt::Dbo;

class Project;  //forward declaration, for testing

class RiskItem : public dbo::Dbo<RiskItem> {
private:
    int         riskID;
    std::string riskName;
    int         projectID;
    std::string desc;
    int         probability;
    int         impact;
    
public:
    template<class Action>
    void persist(Action& a)
    {
        //dbo::id(a, id, "id");
        //Switched out belongsTo with field
        dbo::field(a, projectID, "projectID");
        dbo::field(a, riskName, "riskName");
        dbo::field(a, desc, "desc");
        dbo::field(a, probability, "probability");
        dbo::field(a, impact, "impact");
    }

    // Constructor
    RiskItem() : riskID(0), projectID(0), probability(0), impact(0) {
	}

    // Getters
    int getRiskID() const { 
		return riskID; 
	}
    std::string getRiskName() const { 
		return riskName; 
	}
    int getProjectID() const { 
		return projectID; 
	}
    std::string getDesc() const { 
		return desc; 
	}
    int getProbability() const { 
		return probability; 
	}
    int getImpact() const { 
		return impact; 
	}

    // Setters
    void setRiskID(int id) { 
		riskID = id; 
	}
    void setRiskName(const std::string& name) { 
		riskName = name; 
	}
    void setProjectID(int projID) { 
		projectID = projID; 
	}
    void setDesc(const std::string& description) { 
		desc = description; 
	}
    void setProbability(int prob) { 
		probability = prob; 
	}
    void setImpact(int imp) { 
		impact = imp; 
	}
};

#endif // RISKITEM_H
