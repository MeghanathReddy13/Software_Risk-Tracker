# Role Model Assessment  
### Risk Tracker  
### Date: 5/3/2026  

---

## Components:  
* model: roleModel.h roleModel.cpp
* manager: databaseManager.h databaseManager.cpp
* verifier: roleTest.cpp

---

## Test Results  

| Test Case Name                         | Scenario                                           | Expected Result                                              | Status |
| -------------------------------------  | ---------------------------------------------------| ------------------------------------------------------------ | ------ |
| FullLifecycle                          | Create, persist, retrieve, and delete a Role object| Object maintains data integrity throughout the entire session| PASSED |

---

### Execution Log
[==========] Running 1 test from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 3 tests from RoleTest.<br>
[RUN       ] RoleTest.FullLifecycle<br>
[        OK] RoleTest.Fulllifecycle<br>
[----------] 1 test from RoleTest<br>
[----------] Global test environment tear-down<br>
[==========] 1 test1 from 1 test suite ran.<br>
