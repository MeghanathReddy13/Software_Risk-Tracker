# systemVerification.md
## Performance & Safety Guard Verification Report
### 1. Executive Summary
This report documents the verification of Performance requirements (**PERF-1** through **PERF-7**), Safety requirements (**SAFE-1** and **SAFE-2**), Security requirements (**SEC-2** and **SEC-5**), and Functional requirements (**FUNC-5** and **FUNC-6**). Testing was conducted on April 29, 2026, using browser-based profiling tools and manual logic audits.

### 2. Performance Metrics Summary

| Req ID | Requirement Description | Status | Comments/Methods|
| :--- | :--- | :--- | :---:|
| **PERF-1** | 20 Concurrent Users Support < 2.0s | **PASS** |Allie opened 10 tabs and logged in, and performed actions in each tab. Hannah did the same. |
| **PERF-2** | Risk create edit delete risks response time < 2.0s | **PASS** | Created, Deleted, and Edited Users |
| **PERF-3** | Save risk input response time < 1.0s | **PASS** |Saved Project|
| **PERF-4** | Initial Page Load < 5.0s | **PASS** |Connect to the application.|
| **PERF-5** | Risk matrix generation time < 4.0s | **PASS** |Load up the Risk Matrix|
| **PERF-6** | Matrix update after risk change < 2.0s | **PASS** |Made a risk and logged out and logged back in to ensure it stayed stored.|
| **PERF-7** | CSV export completion time < 2.0s | **PASS** |Exported CSV|
| **SAFE-1** | Require user to confirm any deletion action| **PASS** |Created and deleted projects and users|
| **SAFE-2** | Auto-logout session after 15m of inactivity| **PASS** |Waited 15 min to be timed out.|
| **SEC-2** |  User data securely stored against data loss| **PASS** |Created Users and Projects, Logged out and Logged in, the data was still there.|
| **SEC-5** | Reset a user's password via admin | **PASS** |Login as admin and reset user's password|
| **FUNC-5** | Store all data and provide CSV export feature| **PASS** |Data is saved in the download|
| **FUNC-6** |  Dynamic color-coded matrix (Likelihood × Impact)| **PASS** |Color-Coded matrix is displayed with Likelihood and Impact|

### 3. Verification Sign-off

| Role | Name | Date | Status |
| :--- | :--- | :--- | :--- |
| **Lead Tester** | Hannah Lanier | 2026-05-01 | **VERIFIED** |
| **Peer Reviewer** | Alli Ornelas| 2026-05-01 | **VERIFIED** |

**Reviewer Comments:**
"Performance was measured under simulated load. Response times consistently fall significantly below the maximum thresholds defined in the SRS."
