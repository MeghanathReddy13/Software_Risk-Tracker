// dbmTest.cpp
#include "dbmTest.h"
#include <gtest/gtest.h>

//Adding a user
TEST_F(DatabaseManagerTest, AddUserTest) {
    User u;
    u.setName("Alice");
    u.setUserName("alice123");
    u.setPassHash("hashedpw");

    int added = dbm.addUser(u);
    u.setID(added);
    EXPECT_EQ(added, u.getID());

    //Fetch by username
    std::string username = u.getUserName();
    User fetched = dbm.getUserByIdentity(username);
    EXPECT_EQ(fetched.getName(), "Alice");
    EXPECT_EQ(fetched.getUserName(), "alice123");
    EXPECT_EQ(fetched.getPassHash(), "hashedpw");
}

TEST_F(DatabaseManagerTest, EditUserTest) {
    User u;
    u.setName("Bob");
    u.setUserName("bob123");
    u.setPassHash("pw1");

    int added = dbm.addUser(u);
    u.setID(added);

    // Edit user
    u.setName("Bob Edited");
    u.setPassHash("pw2");
    //bool edited = dbm.editUser(u);
    int edited = dbm.editUser(u);

    EXPECT_EQ(edited, u.getID());
    
    std::string username = u.getUserName();
    User fetched = dbm.getUserByIdentity(username);
    EXPECT_EQ(fetched.getName(), "Bob Edited");
    EXPECT_EQ(fetched.getPassHash(), "pw2");
}

TEST_F(DatabaseManagerTest, DeleteUserTest) {
    User u;
    u.setName("Charlie");
    u.setUserName("charlie123");
    dbm.addUser(u);

    int id = u.getID();
    int deleted = dbm.deleteUser(id);
    EXPECT_EQ(deleted, 1);

    std::string username = u.getUserName();
    User fetched = dbm.getUserByIdentity(username);
    EXPECT_EQ(fetched.getID(), -1); //assuming getUserByIdentity returns default User if not found
}

TEST_F(DatabaseManagerTest, GetAllUsersTest) {
    //Add multiple users
    User u1; u1.setName("Dan"); u1.setUserName("dan123"); dbm.addUser(u1);
    User u2; u2.setName("Eve"); u2.setUserName("eve123"); dbm.addUser(u2);

    std::vector<User> users = dbm.getAllUsers();
    EXPECT_GE(users.size(), 2);

    bool foundDan = false, foundEve = false;
    for (const auto& u : users) {
        if (u.getUserName() == "dan123") foundDan = true;
        if (u.getUserName() == "eve123") foundEve = true;
    }
    EXPECT_TRUE(foundDan);
    EXPECT_TRUE(foundEve);
}

