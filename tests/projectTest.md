# Project Model and Manager Assessment  
### Risk Tracker  
### Date: 5/3/2026  

---

## Components:  
* model: projectModel.h projectModel.cpp
* manager: projectManagerModel.h projectManagerModel.cpp
* verifier: projectModelTest.cpp projectManagerTest.cpp

---

## Test Results  

| Test Case Name                         | Scenario                                      | Expected Result                          | Status |
| -------------------------------------  | ----------------------------------------------| ---------------------------------------- | ------ |
| DefaultValues                          | Initialize New Project                        | ID defaults to -1, counts to 5           | PASSED |
| GettersAndSetters                      | Set/retrieve all project fields               | Retrieved values match input             | PASSED |
| DatabasePersistence                    | Round-trip DBO save/load                      | Data is successfully stored in DB        | PASSED |
| DeleteProjectSuccess                   | Create then delete a project                  | Record is removed from DB                | PASSED |
| HandleInvalidProjectID                 | Attempt actions with ID of -1                 | Manager fails gracefully (returns false) | PASSED |

---

### Execution Log
[==========] Running 3 tests from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 3 tests from ProjectModelTest.<br>
[RUN       ] ProjectModelTest.GettersAndSetters<br>
[        OK] ProjectModelTest.GettersAndSetters (7 ms)<br>
[RUN       ] ProjectModelTest.DatabasePersistence<br>
[        OK] ProjectModelTest.DatabasePersistence (6 ms)<br>
[RUN       ] ProjectModelTest.DefaultValues<br>
[        OK] ProjectModelTest.DefaultValues (1 ms)<br>
[----------] 3 tests from projectModelTest (15 ms total)<br>
[----------] Global test environment tear-down<br>
[==========] 3 tests from 1 test suite ran. (17 ms total)<br>
[  PASSED  ] 3 tests.

[==========] Running 4 tests from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 4 tests from ProjectManagerTest<br>
[RUN       ] ProjectManagerTest.AddProjectSuccess<br>
[        OK] ProjectManagerTest.AddProjectSuccess (12 ms)<br>
[RUN       ] ProjectManagerTest.UpdateProjectSuccess<br>
[        OK] ProjectManagerTest.UpdateProjectSuccess (2 ms)<br>
[RUN       ] ProjectManagerTest.DeleteProjectSuccess<br>
[        OK] ProjectManagerTest.DeleteProjectSuccess (3 ms)<br>
[RUN       ] ProjectManagerTest.HandleInvalidProjectID<br>
[        OK] ProjectManagerTest.HandleInvalidProjectID (0 ms)<br>
[----------] 4 tests from ProjectManagerTest (19 ms total)<br>
[----------] Global test environment tear-down<br>
[==========] 4 tests from 1 test suite ran. (20 ms total)<br>
[  PASSED  ] 4 tests.

