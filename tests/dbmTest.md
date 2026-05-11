# dbmTest.md
## Unit Testing: Database Manager Operations

### 1. Overview
The `dbmTest.cpp` suite utilizes the GoogleTest framework to verify the **DatabaseManager** component. These tests ensure that the system handles User lifecycle management and relational data persistence according to the project’s security and functional requirements.

### 2. Test Execution Summary

| Test Case | Description | Result |
| :--- | :--- | :---: |
| `AddUserTest` | Verifies a user can be added and retrieved by identity. | **PASS** |
| `EditUserTest` | Validates that existing user attributes (Name, PassHash) update correctly. | **PASS** |
| `DeleteUserTest` | Confirms users are removed and no longer retrievable. | **PASS** |
| `GetAllUsersTest` | Tests batch retrieval of all user entities for administrative view. | **PASS** |

### 3. Requirements Verification

* **SECU-1 (Authentication):** Verified that `userName` and `passHash` are stored and retrievable for the authentication handshake.
* **FUNC-7 (User Access):** Verified that user-specific identities can be fetched accurately from the data layer.
* **FUNC-8 (Admin Management):** Verified the administrative capabilities including adding, editing, and deleting user records.

