# User & UserManager Assessment  
### Risk Tracker  
### Date: 4/8/2026  

---

## Components:  
* model: userModel.h, userModel.cpp
* manager: userManagerModel.h, userManagerModel.cpp
* verifier: userTest.cpp

---

## Traceability Matrix  

| Requirement                  | Implementation                                  | Verified By                                      |
| ---------------------------- | ----------------------------------------------- | ------------------------------------------------ |
| User Default Initialization  | User() constructor                              | InitializingExpectedValues                       |
| User ID Set/Get              | setID(), getID()                                | SetAndGetID                                      |
| User Name Set/Get            | setName(), getName()                            | SetAndGetName                                    |
| Username Set/Get             | setUserName(), getUserName()                    | SetAndGetUserName                                |
| Password Hash Set/Get        | setPassHash(), getPassHash()                    | SetAndGetPassHash                                |
| User Role Storage            | User::roles vector                              | SetAndGetRole                                    |
| User Project Storage         | User::projects vector                           | SetAndGetProjects                                |
| User Last Action Tracking    | setLastAction(), getLastAction()                | SetAndGetLastAction                              |
| UserManager Initial State    | UserManager constructor                         | LoggedOutFirst                                   |
| Login Input Validation       | UserManager::login()                            | EmptyUsernameLoginFail, EmptyPasswordLoginFail   |
| Logout Behavior              | UserManager::logout()                           | LogoutWhenLoggedOut                              |
| Admin Check Logic            | UserManager::isAdmin()                          | AdminFalseWhenLoggedOut                          |
| Idle Timeout Safety          | UserManager::idleTimer()                        | IdleTimerDoesNothingIfLoggedOut                  |

---

## Test Results  

| Test Case Name                         | Scenario                                      | Expected Result                          | Status |
| ------------------------------------- | ---------------------------------------------- | ---------------------------------------- | ------ |
| InitializingExpectedValues            | Create new User                                | Default values correctly initialized     | PASSED |
| SetAndGetID                           | Set and retrieve user ID                       | ID matches expected                      | PASSED |
| SetAndGetName                         | Set and retrieve name                          | Name matches expected                    | PASSED |
| SetAndGetUserName                     | Set and retrieve username                      | Username matches expected                | PASSED |
| SetAndGetPassHash                     | Set and retrieve password hash                 | Hash matches expected                    | PASSED |
| SetAndGetRole                         | Assign roles to user                           | Roles stored and retrieved correctly     | PASSED |
| SetAndGetProjects                     | Assign projects to user                        | Projects stored and retrieved correctly  | PASSED |
| SetAndGetLastAction                   | Assign last action                             | Last action stored correctly             | PASSED |
| LoggedOutFirst                        | Initialize UserManager                         | No user logged in                        | PASSED |
| AdminFalseWhenLoggedOut               | Check admin status when not logged in          | Returns false                            | PASSED |
| EmptyUsernameLoginFail                | Login with empty username                      | Login returns false                      | PASSED |
| EmptyPasswordLoginFail                | Login with empty password                      | Login returns false                      | PASSED |
| LogoutWhenLoggedOut                   | Logout without active session                  | No crash, state unchanged                | PASSED |
| IdleTimerDoesNothingIfLoggedOut       | Trigger idle timer without login               | No logout or crash                       | PASSED |

---

## Technical Implementation  

```
// Example: Test cases
TEST_F(UserTest, SetAndGetUserName) {
    user.setUserName("spiderman");
    EXPECT_EQ(user.getUserName(), "spiderman");
}

TEST_F(UserManagerTest, EmptyUsernameLoginFail) {
    EXPECT_FALSE(userManager->login("", "password"));
    EXPECT_FALSE(userManager->isLoggedIn());
}
```

### Execution Log
[==========] Running 14 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 8 tests from UserTest
[ RUN      ] UserTest.InitializingExpectedValues
[       OK ] UserTest.InitializingExpectedValues (0 ms)
[ RUN      ] UserTest.SetAndGetID
[       OK ] UserTest.SetAndGetID (0 ms)
[ RUN      ] UserTest.SetAndGetName
[       OK ] UserTest.SetAndGetName (0 ms)
[ RUN      ] UserTest.SetAndGetUserName
[       OK ] UserTest.SetAndGetUserName (0 ms)
[ RUN      ] UserTest.SetAndGetPassHash
[       OK ] UserTest.SetAndGetPassHash (0 ms)
[ RUN      ] UserTest.SetAndGetRole
[       OK ] UserTest.SetAndGetRole (0 ms)
[ RUN      ] UserTest.SetAndGetProjects
[       OK ] UserTest.SetAndGetProjects (0 ms)
[ RUN      ] UserTest.SetAndGetLastAction
[       OK ] UserTest.SetAndGetLastAction (0 ms)
[----------] 8 tests from UserTest (0 ms total)

[----------] 6 tests from UserManagerTest
[ RUN      ] UserManagerTest.LoggedOutFirst
Dbo.backend.Sqlite3: begin transaction
Dbo.backend.Sqlite3: rollback transaction
[       OK ] UserManagerTest.LoggedOutFirst (8 ms)
[ RUN      ] UserManagerTest.AdminFalseWhenLoggedOut
[       OK ] UserManagerTest.AdminFalseWhenLoggedOut (0 ms)
[ RUN      ] UserManagerTest.EmptyUsernameLoginFail
[       OK ] UserManagerTest.EmptyUsernameLoginFail (0 ms)
[ RUN      ] UserManagerTest.EmptyPasswordLoginFail
[       OK ] UserManagerTest.EmptyPasswordLoginFail (0 ms)
[ RUN      ] UserManagerTest.LogoutWhenLoggedOut
[       OK ] UserManagerTest.LogoutWhenLoggedOut (0 ms)
[ RUN      ] UserManagerTest.IdleTimerDoesNothingIfLoggedOut
[       OK ] UserManagerTest.IdleTimerDoesNothingIfLoggedOut (0 ms)
[----------] 6 tests from UserManagerTest (9 ms total)

[----------] Global test environment tear-down
[==========] 14 tests from 2 test suites ran. (11 ms total)
[  PASSED  ] 14 tests.

