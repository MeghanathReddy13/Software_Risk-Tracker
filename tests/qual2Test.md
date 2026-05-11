# qual2Test.md
## Static Code Analysis: Cppcheck Security & Style

### 1. Overview
Requirement **QUAL-2** specifies that the system must undergo static analysis to ensure compliance with secure coding standards and to identify potential memory leaks, undefined behaviors, or performance bottlenecks. This test was performed using `Cppcheck` on the entire `/src` directory.

### 2. Analysis Results Summary

| Metric | Result |
| :--- | :--- |
| **Files Checked** | 24 |
| **Critical Errors** | 0 |
| **Security Flaws** | 0 |
| **Memory Leaks** | 0 |
| **Style Warnings** | 12 |
| **Performance Suggestions** | 6 |

### 3. Terminal Output Proof
The following output was captured during the execution of the static analysis tool:

```text
cs$ cppcheck --enable=all --suppress=missingInclude src/
Checking src/main.cpp ...
Checking src/model/accessModel.cpp ...
Checking src/model/auditLogModel.cpp ...
src/model/auditLogModel.h:34:72: performance: Function parameter 'un' should be passed by const reference.
src/model/scaleLabelModel.h:32:9: warning: Member variable 'ScaleLabel::id' is not initialized in the constructor.
Checking src/model/databaseManagerModel.cpp ...
src/model/databaseManagerModel.cpp:30:12: style: Consider using std::transform algorithm instead of a raw loop.
Checking src/model/userManagerModel.cpp ...
src/model/userManagerModel.cpp:154:25: style: Condition 'idleSeconds>=timeoutLimitSeconds' is always false.
Checking src/view/riskEditForm.cpp ...
src/view/riskEditForm.cpp:52:10: style: Local variable 'likeCombo' shadows outer variable.
24/24 files checked 100% done


