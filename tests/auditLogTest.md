# Audit Log Model Assessment  
### Risk Tracker  
### Date: 5/3/2026  

---

## Components:  
* model: auditLogModel.h auditLogModel.cpp
* manager: databaseManagerModel.h databaseManagerModel.cpp
* verifier: auditLogTest.cpp

---

## Test Results  

| Test Case Name                         | Scenario                                      | Expected Result                                   | Status |
| -------------------------------------  | ----------------------------------------------| --------------------------------------------------| ------ |
| ConstructorAndGetters                  | Initialize AuditLog with sample data          | Getters return the matching initial values        | PASSED |
| Setters                                | Update existing AuditLog fields               | Fields reflect the newly assigned values          | PASSED |
| DatabasePersistence                    | Write log to DB and retrieve it               | Log is successfully stored and remains identical  | PASSED |

---

### Execution Log
[==========] Running 3 tests from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 3 tests from AuditLogTest.<br>
[RUN       ] AuditLogTest.ConstructorAndGetters<br>
[        OK] AuditLogTest.ConstructorAndGetters<br>
[RUN       ] AuditLogTest.Setters<br>
[        OK] AuditLogTest.Setters<br>
[RUN       ] AuditLogTest.DatabasePersistence<br>
[        OK] AuditLogTest.DatabasePersistence<br>
[----------] 3 tests from AuditLogTest<br>
[----------] Global test environment tear-down<br>
[==========] 3 tests from 1 test suite ran.<br>
