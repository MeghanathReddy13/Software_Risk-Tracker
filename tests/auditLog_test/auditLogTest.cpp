/* Josh Nettle */
/* 05/03/2026 */
#include <gtest/gtest.h>
#include <memory>
#include <chrono>
#include <vector>
#include <string>
#include "auditLogModel.h"
#include "databaseManagerModel.h"

class AuditLogTest : public ::testing::Test {
protected: 
	std::shared_ptr<DatabaseManager> db;

	void SetUp() override {
		db = std::make_shared<DatabaseManager>();
	}
};

TEST_F(AuditLogTest, ConstructorAndGetters) {
	auto now = std::chrono::system_clock::now();
	std::string user = "admin_user";
	std::string evType = "LOGIN";
	std::string enType = "USER_SESSION";
	std::string detail = "User logged in successfully";

	AuditLog log(now, user, evType, enType, detail);
	
	EXPECT_EQ(log.getTimestamp(), now);
	EXPECT_EQ(log.getUsername(), user);
	EXPECT_EQ(log.getEventType(), evType);
	EXPECT_EQ(log.getEntityType(), enType);	
	EXPECT_EQ(log.getDetails(), detail);	
}

TEST_F(AuditLogTest, Setters) {
	AuditLog log;
	auto now = std::chrono::system_clock::now();

	log.setTimestamp(now);
	log.setUsername("editor_1");
	log.setEventType("UPDATE");
	log.setEntityType("RISK_ITEM");
	log.setDetails("Modified risk record #101");

	EXPECT_EQ(log.getTimestamp(), now);
	EXPECT_EQ(log.getUsername(), "editor_1");
	EXPECT_EQ(log.getEventType(), "UPDATE");
	EXPECT_EQ(log.getEntityType(), "RISK_ITEM");
	EXPECT_EQ(log.getDetails(), "Modified risk record #101");
}

TEST_F(AuditLogTest, DatabasePersistence) {
	auto now = std::chrono::system_clock::now();
	std::string uniqueDetail = "Integration_Test_Detail_123";

	db->logActivity(now, "test_user", "TEST_EVENT", "TEST_ENTITY", uniqueDetail);

	auto& session = Database::instance().session();
	dbo::Transaction t(session);

	dbo::ptr<AuditLog> found = session.find<AuditLog>().where("details = ?").bind(uniqueDetail);

	ASSERT_TRUE(found) << "The AuditLog was not found in the database after calling logActivity.";
	EXPECT_EQ(found->getUsername(), "test_user");
	EXPECT_EQ(found->getEventType(), "TEST_EVENT");

	t.commit();	
}
