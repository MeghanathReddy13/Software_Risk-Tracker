/* Josh Nettle */
/* 4/7/2026 */
#include <gtest/gtest.h>
#include <Wt/Dbo/Transaction.h>
#include <memory>
#include "roleModel.h"
#include "userModel.h"
#include "databaseManagerModel.h"

class RoleTest : public ::testing::Test {
protected:
	void SetUp() override {
	auto& session = Database::instance().session();

	dbo::Transaction t(session);
	try {
		session.mapClass<User>("user");
		session.mapClass<Role>("role");
		session.createTables();
	} catch (...) {
		// Tables should already exist
	}
	t.commit();
	}
};

TEST_F(RoleTest, FullLifecycle) {
	auto& session = Database::instance().session();
	dbo::ptr<Role> rolePtr;
	int userId = -1;

	{
		dbo::Transaction t(session);
		auto user = std::make_unique<User>();
		user->setUserName("role_tester");
		dbo::ptr<User> userPtr = session.add(std::move(user));

		auto role = std::make_unique<Role>(userPtr, "InitialRole");
		rolePtr = session.add(std::move(role));
		t.commit();
		userId = userPtr.id();
	}

	{
		dbo::Transaction t(session);
		rolePtr.modify()->setRoleTitle("SuperUser");
		t.commit();
	}

	{
		dbo::Transaction t(session);
		EXPECT_EQ(rolePtr->getRoleTitle(), "SuperUser");
		ASSERT_TRUE(rolePtr->getUser());
		EXPECT_EQ(rolePtr->getUser().id(), userId);

		rolePtr.remove();
		t.commit();
	}
}
	

