/* Brandon Zuniga */
/* 2/20/2026 */
#include "riskManagerModel.h"
#include <iostream>

RiskManager::RiskManager(std::shared_ptr<DatabaseManager> db)
    : status("Initialized"), newData(""), dbManager_(db) {}	

// Adds a new risk to the system
void RiskManager::addRisk(int projectID, const std::string& riskName, const std::string& desc, int probability, int impact) {
    // Create the new risk object
    RiskItem newRisk;
    newRisk.setRiskName(riskName);
    newRisk.setDesc(desc);
    newRisk.setProbability(probability);
    newRisk.setImpact(impact);
    newRisk.setProjectID(projectID);

    // Save to database
    // By alli: changes -> to . (applied to all dbManager uses)
    dbManager_->addRisk(newRisk); // Fixed
    
    this->setStatus("Risk created successfully");
}

// Updates an existing risk
void RiskManager::updateRisk(int riskID, const std::string& newData, int likelihood, int impact) {
    // Find the risk in the database [cite: 680-681]
    //RiskItem risk = DatabaseManager::getInstance().getRiskById(riskID);
    RiskItem risk = dbManager_->getRiskById(riskID);
    
    this->setNewData(newData);
    risk.setDesc(newData);
    // added for functionality in riskEditForm  NG
    risk.setProbability(likelihood);
    risk.setImpact(impact);
    
    // Save the updated risk back to the database
    //DatabaseManager::getInstance().editRisk(risk);
    dbManager_->editRisk(risk);
    
    this->setStatus("Risk updated");
}

// Deletes an existing risk NG
void RiskManager::deleteRisk(int riskID) {
    RiskItem risk = dbManager_->getRiskById(riskID);
    dbManager_->deleteRisk(risk);

    this->setStatus("Risk deleted");
}

// Retrieves all risks for a given project
std::vector<RiskItem> RiskManager::listRisks(int projectID) {
    std::vector<RiskItem> risks;
    
    //risks = DatabaseManager::getInstance().getRisksByProject(projectID);
    risks = dbManager_->getRisksByProject(projectID);

    return risks;
}

// Getters
std::string RiskManager::getStatus() const { 
	return status; 
}

std::string RiskManager::getNewData() const { 
	return newData; 
}

// Setters
void RiskManager::setStatus(const std::string& newStatus) { 
	status = newStatus; 
}
	
void RiskManager::setNewData(const std::string& data) { 
	newData = data; 
}
