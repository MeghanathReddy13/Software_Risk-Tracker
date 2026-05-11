# Risk Item Model Assessment  
### Risk Tracker  
### Date: 5/3/2026  

---

## Components:  
* model: riskItemModel.h riskItemModel.cpp
* manager: databaseManagerModel.h databaseManagerModel.cpp
* verifier: riskItemTest.cpp

---

## Test Results  

| Test Case Name                         | Scenario                                      | Expected Result                                   | Status |
| -------------------------------------  | ----------------------------------------------| --------------------------------------------------| ------ |
| SettersAndGetters                      | Assign values to a RiskItem                   | Getters return precise values assigned            | PASSED |
| DatabasePersistence                    | Save a new RiskItem to the database           | Item is retrievable with all fields intact        | PASSED |
| EditRiskPersistence                    | Modify an existing database Risk entry        | Database reflects the updated values correctly    | PASSED |

---

### Execution Log
[==========] Running 3 tests from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 3 tests from RiskItemTest.<br>
[RUN       ] RiskItemTest.SettersAndGetters<br>
[        OK] RiskItemTest.SettersAndGetters<br>
[RUN       ] RiskItemTest.DatabasePersistence<br>
[        OK] RiskItemTest.DatabasePersistence<br>
[RUN       ] RiskItemTest.EditRiskPersistence<br>
[        OK] RiskItemTest.EditRiskPersistence<br>
[----------] 3 tests from RiskItemTest<br>
[----------] Global test environment tear-down<br>
[==========] 3 tests from 1 test suite ran.<br>
