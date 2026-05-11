# RTVM
## Risk Tracker Project


| Component | Req ID | Requirement Description | Test Passed | Status |
| :--- | :--- | :--- | :--- | :---: |
| **SoD** | **PERF-1** | Support 20 concurrent users with < 2s response time |[systemVerification.md](/tests/systemVerification.md) |**PASS**  |
| **SoD** | **PERF-2** | Risk create edit delete risks response time < 2s |[systemVerification.md](/tests/systemVerification.md) |**PASS**  |
| **SoD** | **PERF-3** | Save risk input response time < 1s |[systemVerification.md](/tests/systemVerification.md) |**PASS**  |
| **SoD** | **PERF-4** | Page load response time < 5s |[systemVerification.md](/tests/systemVerification.md) |**PASS**  |
| **SoD** | **PERF-5** | Risk matrix generation time < 4s |[systemVerification.md](/tests/systemVerification.md) |**PASS** |
| **SoD** | **PERF-6** | Matrix update after risk change < 2s |[systemVerification.md](/tests/systemVerification.md) | **PASS** |
| **SoD** | **PERF-7** | CSV export completion time < 2s |[systemVerification.md](/tests/systemVerification.md) - [exportTest](/tests/exportTest) |**PASS**  |
| **UI** | **SAFE-1** | Require user to confirm any deletion action |[systemVerification.md](/tests/systemVerification.md) |**PASS**  |
| **AUM** | **SAFE-2** | Auto-logout session after 15m of inactivity | [userTest.md](/tests/userTest.md) - [/tests/userTest](/tests/userTest), [dbm.md](/test/dbmTest.md) - [/tests/dbmTest](/tests/dbmTest)[systemVerification.md](/tests/systemVerification.md) | **PASS** |
| **AUM** | **SECU-1** | Authentication required before app access |[userTest.md](/tests/userTest.md) - [/tests/userTest](/tests/userTest),| **PASS** |
| **SoD** | **SECU-2** | User data securely stored against data loss |[systemVerification.md](/tests/systemVerification.md) |**PASS**  |
| **AUM, SoD** | **SECU-3** | Passwords stored with secure hashing algorithm |  [userTest.md](/tests/userTest.md) - [/tests/userTest](/tests/userTest), [dbm.md](/test/dbmTest.md) - [/tests/dbmTest](/tests/dbmTest)  | **PASS** |
| **AUM, SoD** | **SECU-4** | Record logins, create, delete, edit and CSV exports | [dbTest.md](/tests/dbTest.md) - [/tests/dbTest](/tests/dbTest) | **PASS** |
| **AUM** | **SECU-5** | Reset a users password via admin |[systemVerification.md](/tests/systemVerification.md)  |**PASS**  |
| **Style** | **QUAL-1** | Follow Mozilla C++ coding style |[styleTest.md](/test/styleTest.md) |**PASS** |
| **Style** | **QUAL-2** | Follow SEI secure coding style (Cppcheck) |[qual2Test.md](/test/qual2Test.md) |**PASS** |
| **UI** | **QUAL-3** | Meet WCAG 2.1 accessibility standards |[Qual3.md](/tests/Qual3.md) | **PASS**|
| **UI, API** | **FUNC-1** | Create project by defining a project name | [userTest.md](/tests/userTest.md) - [/tests/userTest](/tests/userTest) [AccessModelT](/tests/AccessModelT) | **PASS** |
| **AUM** | **FUNC-2** | Auth required before accessing project data | [userTest.md](/tests/userTest.md) - [/tests/userTest](/tests/userTest) | **PASS** |
| **UI, RM** | **FUNC-3** | Input risk data (ID, Desc, Likelihood, Impact) | [AccessModelT](/tests/AccessModelT) - [AccessModelT.md](/tests/AccessModelT.md) | **PASS** |
| **UI, API** | **FUNC-4** | Define matrix dimensions during project creation | [AccessModelT](/tests/AccessModelT) - [AccessModelT.md](/tests/AccessModelT.md) | **PASS** |
| **SoD** | **FUNC-5** | Store all data and provide CSV export feature |[systemVerification.md](/tests/systemVerification.md) |**PASS** |
| **UI, API** | **FUNC-6** | Dynamic color-coded matrix (Likelihood × Impact) |[systemVerification.md](/tests/systemVerification.md) |**PASS**  |
| **AUM** | **FUNC-7** | Regular users can access and edit projects | [dbTest.md](/tests/dbTest.md) - [/tests/dbTest](/tests/dbTest), [/tests/riskManagerTest](/tests/riskManager_test), [dbm.md](/test/dbmTest.md) - [/tests/dbmTest](/tests/dbmTest) | **PASS** |
| **AUM** | **FUNC-8** | Admin users can manage all users and projects | [dbTest.md](/tests/dbTest.md) - [/tests/dbTest](/tests/dbTest), [userTest.md](/tests/userTest.md) - [/tests/userTest](/tests/userTest), [dbm.md](/test/dbmTest.md) - [/tests/dbmTest](/tests/dbmTest) | **PASS** |
| **UI** | **FUNC-9** | Comply with WCAG accessibility guidelines |[Func9.md](/tests/Func9.md) | **PASS**|




