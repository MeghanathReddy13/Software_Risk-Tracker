# Database Manager Assessment
### Risk Tracker
### Date: 2/18/2026
### Updated: 5/3/2026


## Components: 
* manager: DatabaseManager.h, DatabaseManager.cpp
* schema: RiskSchema.h
* verifier: DatabaseTest


### Traceability Matrix
| Requirement                  | Implementation                             | Verified By              |
| ---------------------------- | ------------------------------------------ | ------------------------ |
| Singleton Connection         | DatabaseManager::instance()                | singletonConnection      |
| User Create/Delete           | session().add(), remove()                  | UserCreateDelete         |
| User Role Relationship       | Role.user foreign key                      | UserRole                 |
| Project Risk Relationship    | Risk.project foreign key                   | ProjectRiskRelation      |
| Project Access Mapping       | Access.user & Access.project               | ProjectAccess            |
| Scale Label Storage          | ScaleLabel entity mapping                  | ScaleLabel               |
| Audit Logging (LOGIN)        | AuditLog entity mapping                    | AuditLogEntry            |
| Audit Logging (CREATE)       | AuditLog on entity creation                | UserCreateDelete         |
| Audit Logging (DELETE)       | AuditLog on entity deletion                | UserCreateDelete         |
| Audit Logging (EDIT)         | AuditLog on entity modification            | EditLogging              |
| Audit Logging (EXPORT)       | AuditLog on CSV export action              | CSVExportLogging         |

### Test Results
| Test Case Name            | Scenario                                      | Expected Result                           | Status    |  
| ------------------------- | --------------------------------------------- | ----------------------------------------- | --------- |
| singletonConnection       | Intialize DB singleton                        | Transaction opens without exception       | PASSED    |
| UserCreateDelete          | Create and delete user                        | User retrieved with correct data          | PASSED    |
| UserRole                  | Assign role to user                           | Role title equals "admin"                 | PASSED    |
| ProjectRiskRelation       | Create project with linked risk               | Risk retrieved by project ID              | PASSED    |
| ProjectAccess             | Assign user access to project                 | Access links correct project              | PASSED    |
| ScaleLabel                | Create and retrieve scale label               | Label name equals "High Impact"           | PASSED    |
| AuditLogEntry             | Create audit log entry (LOGIN)                | Event type equals "LOGIN"                 | PASSED    |
| EditLogging               | Modify project and log action                 | Event type equals "EDIT"                  | PASSED    |
| CSVExportLogging          | Simulate CSV Export and log action            | Event type equals "EXPORT"                | PASSED    |


### Technical Implementation
```
// Example transaction flow inside DatabaseTest
Wt::Dbo::Transaction transaction(db.session());

auto user = std::make_unique<User>();
user->name = "Peter";
user->email = "peterparker@gmail.com";
user->password = "web125!";

db.session()add(std::move(user));
transaction.commit();

Wt::Dbo::ptr<User> peter = 
    db.session().find<User>().where("name = ?").bind("Peter");

ASSERT_TRUE(peter);
EXPECT_EQ(peter->email, "peterparker@gmail.com");
```

### Execution Log
[==========] Running 9 tests from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 9 tests from DatabaseTest.<br>
[RUN       ] DatabaseTest.singletonConnection<br>
[        OK] DatabaseTest.singletonConnection<br>
[RUN       ] DatabaseTest.UserCreateDelete<br>
[        OK] DatabaseTest.UserCreateDelete<br>
[RUN       ] DatabaseTest.UserRole<br>
[        OK] DatabaseTest.UserRole<br>
[RUN       ] DatabaseTest.ProjectRiskRelation<br>
[        OK] DatabaseTest.ProjectRiskRelation<br>
[RUN       ] DatabaseTest.ProjectAccess<br>
[        OK] DatabaseTest.ProjectAccess<br>
[RUN       ] DatabaseTest.ScaleLabel<br>
[        OK] DatabaseTest.ScaleLabel<br>
[RUN       ] DatabaseTest.AuditLogEntry<br>
[        OK] DatabaseTest.AuditLogEntry<br>
[RUN       ] DatabaseTest.EditLogging<br>
[        OK] DatabaseTest.EditLogging<br>
[RUN       ] DatabaseTest.CSVExportLogging<br>
[        OK] DatabaseTest.CSVExportLogging<br>
[----------] 9 tests from DatabaseTest <br>

[  PASSED  ] 9 tests.
