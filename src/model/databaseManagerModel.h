/* Alli */
/* 03/14/2026 */

#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <vector>
#include <memory>
#include <chrono>
#include <Wt/Dbo/Session.h>

#include "databaseModel.h"
#include "riskItemModel.h"
#include "userModel.h"
#include "roleModel.h"
#include "projectModel.h"
#include "accessModel.h"
#include "scaleLabelModel.h"
#include "auditLogModel.h"
#include "databaseModel.h"

namespace dbo = Wt::Dbo;

class DatabaseManager
{
    private:
        Wt::Dbo::Session& session_;
        //DatabaseManager() : session_(Database::instance().session()) {}
    public:
    /*
        static DatabaseManager& instance() 
        {
                static DatabaseManager mgr;
                //return mgri;
                return mgr;
        }
    */
    DatabaseManager();
       // DatabaseManager() : session_(Database::instance().session() ) {}
						//Keep up with methods already defined in cpp (//*)
        int addUser(User& user); 			//*
        int editUser(const User& user);			//* 
	int deleteUser(int id);				//*
        			
        User getUserByIdentity(const std::string& username);	//* 	
	std::vector<User> getAllUsers();			//* 


        void addRisk(const RiskItem& risk);			//*
        void editRisk(const RiskItem& risk);			//*
        void deleteRisk(const RiskItem& risk);			//*	
        std::vector<RiskItem> getRisksByProject(int pid);	//*
        RiskItem getRiskById(int rid);				//*

        void addProject(const Project& p);			//*				
        void editProject(const Project& p);			//*			
        void deleteProject(const Project& p);			//*
        Project getProjectByID(int id);				//*
        std::vector<Project> getAllProjects();
        void logActivity(std::chrono::system_clock::time_point time, const std::string& username, 
            const std::string& event, const std::string& entity, const std::string& details);	//*;
};
#endif
