# AccessModelT.md
## Unit Testing: Project and Risk Model Integrity

### 1. Overview
The `riskTest.cpp` suite validates the fundamental data structures of the Risk Tracker application using GoogleTest. These tests ensure that project metadata and individual risk attributes are correctly initialized and maintain data integrity throughout the object lifecycle.

### 2. Test Execution Summary

| Test Case | Description | Requirement | Result |
| :--- | :--- | :--- | :---: |
| `DefaultMatrixSize` | Verifies the default 5x5 matrix dimensions (Impact/Probability). | **FUNC-4** | **PASS** |
| `InitializationState`| Ensures projects initialize with -1 IDs and handle name setting. | **FUNC-1** | **PASS** |
| `DataIntegrity` | Validates storage of ID, Description, Likelihood, and Impact. | **FUNC-3** | **PASS** |

### 3. Terminal Output
The following output was captured from the terminal during the automated test execution:

```text
[==========] Running 3 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from ProjectModelTest
[ RUN      ] ProjectModelTest.DefaultMatrixSize
[       OK ] ProjectModelTest.DefaultMatrixSize (0 ms)
[ RUN      ] ProjectModelTest.InitializationState
[       OK ] ProjectModelTest.InitializationState (0 ms)
[----------] 2 tests from ProjectModelTest (0 ms total)

[----------] 1 test from RiskItemModelTest
[ RUN      ] RiskItemModelTest.DataIntegrity
[       OK ] RiskItemModelTest.DataIntegrity (0 ms)
[----------] 1 test from RiskItemModelTest (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 2 test suites ran. (1 ms total)
[  PASSED  ] 3 tests.

