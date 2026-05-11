/* Brandon Zuniga */
/* 2/20/2026 */
#ifndef RISK_MANAGER_MODEL_H
#define RISK_MANAGER_MODEL_H

#include <string>
#include <vector>
#include "riskItemModel.h"
#include "databaseManagerModel.h"

class RiskManager {
private:
    std::string status;
    std::string newData;
    std::shared_ptr<DatabaseManager> dbManager_;
   
public:
    RiskManager(std::shared_ptr<DatabaseManager> db); 

    // Logic Methods
    void addRisk(int projectID, const std::string& riskName, const std::string& desc, int probability, int impact);
    void updateRisk(int riskID, const std::string& newData, int likelihood, int impact);
    void deleteRisk(int riskID);
    std::vector<RiskItem> listRisks(int projectID);

    // Getters
    std::string getStatus() const;
    std::string getNewData() const;

    // Setters
    void setStatus(const std::string& newStatus);
    void setNewData(const std::string& data);
};

#endif // RISK_MANAGER_MODEL_H
