# Risk Manager Assessment  
### Risk Tracker  
### Date: 5/3/2026  

---

## Components:
* model: riskItemModel.h  
* manager: riskManagerModel.h riskManagerModel.cpp
* dependencies: databaseManagerModel.h
* verifier: riskManagerTest.cpp

---

## Test Results  

| Test Case Name                         | Scenario                                      | Expected Result                                                    | Status |
| -------------------------------------  | ----------------------------------------------| ------------------------------------------------------------------ | ------ |
| ConstructorState                       | Initialize RiskManager with a DatabaseManager | Dependency is correctly linked and internal lists are empty        | PASSED |
| AddRiskIntegration                     | Create a risk through the Manager interface   | Risk is validated, passed to the DB, and added to the local view   | PASSED |
| UpdateRiskIntegration                  | Edit an existing risk through the Manager     | Changes propagate to the DB and refresh the local state            | PASSED |
| ListRisksIntegration                   | Retrieve all risks associated with a project  | Returns a complete and accurate list of RiskItem objects           | PASSED |
| GettersAndSetters                      | Manipulate Manager-specific properties        | Internal state variables are updated and retrieved correctly       | PASSED |

---

### Execution Log
[==========] Running 5 tests from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 5 tests from RiskManagerTest.<br>
[RUN       ] RiskManagerTest.ConstructorState<br>
[        OK] RiskManagerTest.ConstructorState<br>
[RUN       ] RiskManagerTest.AddRiskIntegration<br>
[        OK] RiskManagerTest.AddRiskIntegraton<br>
[RUN       ] RiskManagerTest.UpdateRiskIntegration<br>
[        OK] RiskManagerTest.UpdateRiskIntegration<br>
[RUN       ] RiskManagerTest.ListRisksIntegration<br>
[        OK] RiskManagerTest.ListRisksIntegration<br>
[RUN       ] RiskManagerTest.GettersAndSetters<br>
[        OK] RiskManagerTest.GettersAndSetters<br>
[----------] 5 tests from RiskManagerTest<br>
[----------] Global test environment tear-down<br>
[==========] 5 tests from 1 test suite ran.<br>
[  PASSED  ] 5 tests.
