#include <Wt/Dbo/backend/Sqlite3.h>
#include "databaseModel.h"
#include "userModel.h"
#include "roleModel.h"
#include "projectModel.h"
#include "accessModel.h"
#include "scaleLabelModel.h"
#include "riskItemModel.h"
#include "auditLogModel.h"

namespace dbo = Wt::Dbo;

//creates a static object - same instance is used for every access
Database& Database::instance(const std::string& dbFile) {
    static Database instance(dbFile);
    return instance;
}

dbo::Session& Database::session() {
    return session_;
}

//Constructor: connect to database and create tables
Database::Database(const std::string& dbFile) {
    //connection_ = std::make_unique<Wt::Dbo::backend::Sqlite3>(dbFile);
    //connection_->setProperty("show-queries", "true");
    auto sqlite = std::make_unique<dbo::backend::Sqlite3>(dbFile);
    sqlite->setProperty("show-queries", "true");
    
    //session_.setConnection(*connection_);
    session_.setConnection(std::move(sqlite));

    mapClasses();
    createTables();
}

void Database::mapClasses() {
    session_.mapClass<User>("User");
    session_.mapClass<Role>("Role");
    session_.mapClass<Project>("Project");
    session_.mapClass<Access>("Access");
    session_.mapClass<ScaleLabel>("ScaleLabel");
    session_.mapClass<RiskItem>("RiskItem");
    session_.mapClass<AuditLog>("AuditLog");
}

void Database::createTables() {
    try {
        session_.createTables();
    } catch (...) {
        //Tables should already exist
    }
}
