# styleTest.md
## Coding Standards Verification: Mozilla C++ Style

### 1. Overview
Requirement **QUAL-1** requires the source code to adhere to the Mozilla C++ Style Guidelines. This ensures maintainability, readability, and consistency across the project modules.

### 2. Style Audit Criteria
The following Mozilla-specific conventions were audited across the `/src` directory:

| Convention | Mozilla Standard | Implementation in myRisk | Status |
| :--- | :--- | :--- | :---: |
| **Indentation** | 2 Spaces | Consistent 2-space indentation applied. | **PASS** |
| **Class Naming** | PascalCase (e.g. UserModel) | All models and views use PascalCase. | **PASS** |
| **Variable Naming** | camelCase (e.g. userName) | Member variables follow camelCase. | **PASS** |
| **Brace Style** | Attached (Same line) | Braces start on the same line as declarations. | **PASS** |
| **File Headers** | Include Guards | All .h files use `#ifndef` or `#pragma once`. | **PASS** |

### 3. Code Snippet Verification
Example from `riskItemModel.h` showing compliance:
```cpp
class RiskItem {
public:
  void setProbability(int p) {
    probability = p;
  }
private:
  int probability;
};

