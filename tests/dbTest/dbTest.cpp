/*
 * Shelby Stanly
 * Database Test
 * 2/17/2025
 *
 * Updated: 3/15/2026
 * Updated: 5/3/2026
 */
#include <gtest/gtest.h>
#include <string>
#include <Wt/Dbo/Transaction.h>
#include <Wt/WDateTime.h>

#include "accessModel.h"
#include "auditLogModel.h"
#include "databaseModel.h"
#include "projectModel.h"
#include "riskItemModel.h"
#include "roleModel.h"
#include "scaleLabelModel.h"
#include "userModel.h"

namespace dbo = Wt::Dbo;

namespace {
    dbo::Session& getSession() {
        return Database::instance("test.db").session();
    }

    class DatabaseTest : public ::testing::Test {
        protected:
            dbo::Session& session = getSession();
    };

    std::string uniqueName(const std::string& base) {
        return base + "_" + std::to_string(Wt::WDateTime::currentDateTime().toTime_t());
    }

    TEST_F(DatabaseTest, SingletonConnection) {
        //DatabaseManager& db = getDB();
        EXPECT_NO_THROW({
            Wt::Dbo::Transaction transaction(session);
        });
    }

    TEST_F(DatabaseTest, UserCreateDelete) {
        //Create User
        dbo::ptr<User> userPtr;
        {
            dbo::Transaction transaction(session);
            auto newUser = std::make_unique<User>();
            newUser->setName("Peter Parker");
            newUser->setUserName("Peter");
            //newUser->email = "peterparker@gmail.com";
            newUser->setPassHash("web125!");

            //Attempting to add user and commit
            userPtr = session.add(std::move(newUser));

            auto log = std::make_unique<AuditLog>(
                    Wt::WDateTime::currentDateTime(),
                    "Peter",
                    "CREATE",
                    "User",
                    "Created user Peter"
            );
            session.add(std::move(log));

            transaction.commit();
        }

        //Read User
        {
            dbo::Transaction transaction(session);
            dbo::ptr<User> peter = session.find<User>().where("userName = ?").bind("Peter");
            
            ASSERT_TRUE(peter);
            //EXPECT_EQ(peter->email, "peterparker@gmail.com");
            
            
            EXPECT_EQ(peter->getName(), "Peter Parker");
            EXPECT_EQ(peter->getUserName(), "Peter");
            EXPECT_EQ(peter->getPassHash(), "web125!");


            auto log = std::make_unique<AuditLog>(
                    Wt::WDateTime::currentDateTime(),
                    "Peter",
                    "DELETE",
                    "User",
                    "Deleted user Peter"
            );
            session.add(std::move(log));
            peter.remove();
            transaction.commit();
        }

        {
            dbo::Transaction transaction(session);

            dbo::ptr<User> peter = session.find<User>().where("userName = ?").bind("Peter");

            EXPECT_FALSE(peter);
        }
    }

    TEST_F(DatabaseTest, UserRole) {
        //DatabaseManager& db = getDB();
        dbo::ptr<User> userPtr;
        {
            dbo::Transaction transaction(session);

            auto user = std::make_unique<User>();
            user->setName("Otto Octavius");
            user->setUserName("Octavius");
            user->setPassHash("PowerOfTheSun");
            userPtr = session.add(std::move(user));

            auto role = std::make_unique<Role>();
            role->setRoleTitle("admin");
            role->setUser(userPtr);

            session.add(std::move(role));
            transaction.commit();
        }

        {
            dbo::Transaction transaction(session);
            dbo::ptr<User> otto = session.find<User>().where("userName = ?").bind("Octavius");
            ASSERT_TRUE(otto);

            dbo::ptr<Role> role = session.find<Role>().where("user_id = ?").bind(otto.id());
            ASSERT_TRUE(role);
            EXPECT_EQ(role->getRoleTitle(), "admin");

            role.remove();
            otto.remove();
            transaction.commit();
        }
    }

    TEST_F(DatabaseTest, ProjectRiskRelation) {
        std::string projectName = uniqueName("WebFluidDevelopment");
        std::string riskName = uniqueName("CartridgeFailure");

        dbo::ptr<Project> projectPtr;

        {
            dbo::Transaction transaction(session);

            auto project = std::make_unique<Project>();
            project->setName(projectName);
            project->setCreated(Wt::WDateTime::currentDateTime());
            project->setModified(Wt::WDateTime::currentDateTime());
            project->setImpactCount(0);
            project->setProbCount(0);

            projectPtr = session.add(std::move(project));
            session.flush();

            auto risk = std::make_unique<RiskItem>();
            risk->setRiskName(riskName);
            risk->setDesc("Pressurized Web Cartridge Failure");
            risk->setProbability(3);
            risk->setImpact(4);
            risk->setProjectID(projectPtr.id());

            session.add(std::move(risk));
            transaction.commit();
        }

        {
            dbo::Transaction transaction(session);

            dbo::ptr<Project> project = session.find<Project>().where("name = ?")
                .bind(projectName).limit(1);
            ASSERT_TRUE(project);

            dbo::ptr<RiskItem> risk =
                session.find<RiskItem>().where("projectID = ?").bind(projectPtr.id());

            ASSERT_TRUE(risk);
            EXPECT_EQ(risk->getRiskName(), riskName);
            EXPECT_EQ(risk->getProbability(), 3);
            EXPECT_EQ(risk->getImpact(), 4);

            risk.remove();
            project.remove();
            transaction.commit();
        }
    }

    TEST_F(DatabaseTest, ProjectAccess) {
        std::string username = uniqueName("Osborn");
        std::string projectName = uniqueName("AutonomousGlider");

        {
            dbo::Transaction transaction(session);

            auto user = std::make_unique<User>();
            user->setName("Norman Osborn");
            user->setUserName(username);
            user->setPassHash("greenGoblin");
            dbo::ptr<User> userPtr = session.add(std::move(user));

            auto project = std::make_unique<Project>();
            project->setName(projectName);
            project->setCreated(Wt::WDateTime::currentDateTime());
            project->setModified(Wt::WDateTime::currentDateTime());
            project->setImpactCount(0);
            project->setProbCount(0);
            dbo::ptr<Project> projectPtr = session.add(std::move(project));

            auto access = std::make_unique<Access>(userPtr, projectPtr);
            session.add(std::move(access));

            transaction.commit();
        }

        {
            dbo::Transaction transaction(session);

            dbo::ptr<User> osborn =
                session.find<User>().where("userName = ?").bind(username);
            ASSERT_TRUE(osborn);

            dbo::ptr<Access> access =
                session.find<Access>().where("user_id = ?").bind(osborn.id());

            ASSERT_TRUE(access);
            ASSERT_TRUE(access->getProject());
            EXPECT_EQ(access->getProject()->getName(), projectName);

            dbo::ptr<Project> project = access->getProject();

            access.remove();
            project.remove();
            osborn.remove();
            transaction.commit();
        }
    }

    TEST_F(DatabaseTest, ScaleLabel) {
        std::string projectName = uniqueName("ScaleProject");
        std::string labelName = uniqueName("HighImpact");

        {
            dbo::Transaction transaction(session);

            auto project = std::make_unique<Project>();
            project->setName(projectName);
            project->setCreated(Wt::WDateTime::currentDateTime());
            project->setModified(Wt::WDateTime::currentDateTime());
            project->setImpactCount(0);
            project->setProbCount(0);
            dbo::ptr<Project> projectPtr = session.add(std::move(project));

            auto label = std::make_unique<ScaleLabel>(0, projectPtr, 1, labelName, 5);
            session.add(std::move(label));

            transaction.commit();
        }

        {
            dbo::Transaction transaction(session);

            dbo::ptr<ScaleLabel> label =
                session.find<ScaleLabel>().where("name = ?").bind(labelName);

            ASSERT_TRUE(label);
            EXPECT_EQ(label->getName(), labelName);
            EXPECT_EQ(label->getLevel(), 5);
            EXPECT_EQ(label->getType(), 1);

            dbo::ptr<Project> project = label->getProject();

            label.remove();
            if (project) {
                project.remove();
            }
            transaction.commit();
        }
    }

    TEST_F(DatabaseTest, AuditLogEntry) {
        std::string username = uniqueName("admin");

        {
            dbo::Transaction transaction(session);

            auto log = std::make_unique<AuditLog>(
                Wt::WDateTime::currentDateTime(),
                username,
                "LOGIN",
                "User",
                "User logged in from 125.0.0.1"
            );

            session.add(std::move(log));
            transaction.commit();
        }

        {
            dbo::Transaction transaction(session);

            dbo::ptr<AuditLog> log =
                session.find<AuditLog>().where("userName = ?").bind(username);

            ASSERT_TRUE(log);
            EXPECT_EQ(log->getEventType(), "LOGIN");
            EXPECT_EQ(log->getDetails(), "User logged in from 125.0.0.1");
            EXPECT_EQ(log->getEntityType(), "User");

            log.remove();
            transaction.commit();
        }
    }

    TEST_F(DatabaseTest, EditLogging) {
        std::string projectName = uniqueName("Initial Project");
        dbo::ptr<Project> projectPtr;
        {
            dbo::Transaction transaction(session);
            auto project = std::make_unique<Project>();
            project->setName(projectName);
            project->setCreated(Wt::WDateTime::currentDateTime());
            project->setModified(Wt::WDateTime::currentDateTime());
            project->setImpactCount(0);
            project->setProbCount(0);

            projectPtr = session.add(std::move(project));
            transaction.commit();
        }

        {
            dbo::Transaction transaction(session);

            dbo::ptr<Project> project = session.find<Project>()
                .where("name = ?").bind(projectName);
            ASSERT_TRUE(project);

            project.modify()->setName("Updated Project");
            auto log = std::make_unique<AuditLog>(
                    Wt::WDateTime::currentDateTime(),
                    "system",
                    "EDIT",
                    "Project",
                    "Updated project name"
            );
            session.add(std::move(log));

            transaction.commit();
        }

        {
            dbo::Transaction transaction(session);
            dbo::ptr<AuditLog> log = session.find<AuditLog>()
                .where("eventType = ?").bind("EDIT");
            ASSERT_TRUE(log);
            EXPECT_EQ(log->getEventType(), "EDIT");

            log.remove();
            transaction.commit();
        }
    }

    TEST_F(DatabaseTest, CSVExportLogging) {
        std::string username = uniqueName("ExportUser");
        {
            dbo::Transaction transaction(session);

            auto log = std::make_unique<AuditLog>(
                    Wt::WDateTime::currentDateTime(),
                    username,
                    "EXPORT",
                    "CSV",
                    "Exported data to CSV"
            );
            session.add(std::move(log));

            transaction.commit();
        }

        {
            dbo::Transaction transaction(session);
            dbo::ptr<AuditLog> log = session.find<AuditLog>()
                .where("userName = ?").bind(username);
            ASSERT_TRUE(log);
            EXPECT_EQ(log->getEventType(), "EXPORT");

            log.remove();
            transaction.commit();
        }
    }
} //End of namespace
