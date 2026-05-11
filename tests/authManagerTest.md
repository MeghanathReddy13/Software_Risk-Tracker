# Auth Model Assessment  
### Risk Tracker  
### Date: 5/3/2026  

---

## Components:  
* manager: authManagerModel.h authManagerModel.cpp
* verifier: authManagerTest.cpp

---

## Test Results  

| Test Case Name                         | Scenario                                      | Expected Result                              | Status |
| -------------------------------------  | ----------------------------------------------| -------------------------------------------- | ------ |
| VerifyUserSuccess                      | Login with correct username and password      | User is authenitcated; hashes match          | PASSED |
| VerifyUserWrongPassword                | Login with correct username but wrong password| Authentication fails; hashes do not match    | PASSED |
| VerifyUserNotFound                     | Login with a non-existent username            | System returns ID = -1, authentication fails | PASSED |
| VerifyUserEmptyInput                   | Login with missing username or password       | System rejects empty fields gracefully       | PASSED |
| GenerateHashIsConsistent               | Hash the same string multiple times           | Identical inputs produce identical hashes    | PASSED |

---

### Execution Log
[==========] Running 5 tests from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 5 tests from AuthenticatorTest.<br>
[RUN       ] AuthenticatorTest.VerifyUserSuccess<br>
[        OK] AuthenticatorTest.VerifyUserSuccess (18 ms)<br>
[RUN       ] AuthenticatorTest.VerifyUserWrongPassword<br>
[        OK] AuthenticatorTest.VerifyUserWrongPassword (0 ms)<br>
[RUN       ] AuthenticatorTest.VerifyUserNotFound<br>
[        OK] AuthenticatorTest.VerifyUserNotFound (0 ms)<br>
[RUN       ] AuthenticatorTest.VerifyUserEmptyInput<br>
[        OK] AuthenticatorTest.VerifyUserEmptyInput (0 ms)<br>
[RUN       ] AuthenticatorTest.GenerateHashIsConsistent<br>
[        OK] AuthenticatorTest.GenerateHashIsConsistent (0 ms)<br>
[----------] 5 tests from AuthenticatorTest (19 ms total)<br>
[----------] Global test environment tear-down<br>
[==========] 5 tests from 1 test suite ran. (21 ms total)<br>
[  PASSED  ] 5 tests.
