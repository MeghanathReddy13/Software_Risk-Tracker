/* Revised 4/5/2026 */
/* Revised by Brandon Zuniga */
#pragma once    //same as ifndef, define, endif

#include <memory>
#include <string>
#include <Wt/Dbo/Dbo.h>
#include <Wt/WDateTime.h>

namespace Wt {
    namespace Dbo {
        class SqlConnection;
    }
}

class Database {
    public:
        static Database& instance(const std::string& dbFile = "risk.db");
        Wt::Dbo::Session& session();

    private:
        Database(const std::string& dbFile);
        void mapClasses();
        void createTables();

        // Connects to SQLite
        //std::unique_ptr<Wt::Dbo::SqlConnection> connection_;
        Wt::Dbo::Session session_;
};
