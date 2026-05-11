# Login UI Assement
### Risk Tracker
### Date: 2/16/2026

## Components:
* view: login.h, login.cpp
* modle: wittyTest.h, wittyTest.cpp
* verifier: LoginUITest

### Tracebility Matrix
| Requirement     |       Implementation    |    Verified By    |
|-----------------|-------------------------|-------------------|
|Feild Validation |logicModel.attemptLogin()|RejectEmptyUsername|
|Secure Input     |Wt::WPasswordEdit        |visual check       |
|State Feedback   |showError(message)       |RejectEmptyUsername|
|Testability      |friend class LoginUITest |                   |

### Test Results
|   Test Case Name    |      Scenario         |      Expected Result     |Status|
|---------------------|-----------------------|--------------------------|------|
|RejectEmptyUsername  |Username is left blank |"Username cannot be empty"|PASSED|
|RejectEmptyPassword  |Password is left blank |"Password cannot be empty"|PASSED|
|AllowValidCredentials|Valid user and password|"Login Successful"        |PASSED|

### Technical Implementation

,,,
// Logic flow inside login.cpp lambda
std::string userText = username->text().toUTF8();
std::string passText = password->text().toUTF8();
logicModel.attemptLogin(userText, passText); // Handled by wittyTest.cpp
showError(logicModel.getStatus());           // Updates UI state
,,,

### Execution Log
[==========] Running 3 tests from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 3 tests from LoginUITest. <br>
[ RUN      ] LoginUITest.RejectEmptyUsername<br>
[       OK ] LoginUITest.RejectEmptyUsername (2 ms) <br>
[ RUN      ] LoginUITest.RejectEmptyPassword <br>
[       OK ] LoginUITest.RejectEmptyPassword (1 ms) <br>
[ RUN      ] LoginUITest.AllowValidCredentials <br>
[       OK ] LoginUITest.AllowValidCredentials (3 ms) <br>
[----------] 3 tests from LoginUITest (6 ms total) <br>

[  PASSED  ] 3 tests.
