# Login Model Assessment  
### Risk Tracker  
### Date: 5/3/2026  

---

## Components:  
* model: loginModel.h loginModel.cpp
* verifier: loginTest.cpp

---

## Test Results  

| Test Case Name                         | Scenario                                      | Expected Result                              | Status |
| -------------------------------------  | ----------------------------------------------| -------------------------------------------- | ------ |
| AuthorizeSuccess                       | Provide "admin" / "admin"                     | Return true and log success                  | PASSED |
| WrongUserFail                          | Provide "wrongUser" / "admin"                 | Return false and log failure                 | PASSED |
| WrongPassFail                          | Provide "admin" / "wrongPass"                 | Return false and log failure                 | PASSED |
| EmptyInputFail                         | Provide empty strings                         | Return false immediately                     | PASSED |

---

### Execution Log
[==========] Running 4 tests from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 4 tests from LoginTest.<br>
[RUN       ] LoginTest.AuthorizeSuccess<br>
[        OK] LoginTest.AuthorizeSuccess<br>
[RUN       ] LoginTest.WrongUserFail<br>
[        OK] LoginTest.WrongUserFail<br>
[RUN       ] LoginTest.WrongPassFail<br>
[        OK] LoginTest.WrongPassFail<br>
[RUN       ] LoginTest.EmptyInputFail<br>
[        OK] LoginTest.EmptyInputFail<br>
[----------] 4 tests from LoginTest<br>
[----------] Global test environment tear-down<br>
[==========] 4 tests from 1 test suite ran.<br>
