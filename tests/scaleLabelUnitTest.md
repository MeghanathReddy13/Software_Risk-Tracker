# Scale Label Unit Test Assessment
### Risk Tracker
### Date: 4/24/2026
### Updated: 5/3/2026


## Components: 
* model: scaleLabelModel.h, scaleLabelModel.cpp
* verifier: scaleLabelUnitTest


### Traceability Matrix
| Requirement                  | Implementation                             | Verified By              |
| ---------------------------- | ------------------------------------------ | ------------------------ |
| Name Storage                 | setName(), getName()                       | GetandSet                |
| ID Storage                   | setId(), getId()                           | GetandSet                |
| Type Storage                 | setType(), getType()                       | GetandSet                |
| Level Storage                | setLevel(), getLevel()                     | GetandSet                |
| Constructor Initialization   | ScaleLabel()                               | ConstructorInit          |
| Project Association          | setProject(), getProject()                 | ProjectAssignment        |

### Test Results
| Test Case Name            | Scenario                                      | Expected Result                           | Status    |  
| ------------------------- | --------------------------------------------- | ----------------------------------------- | --------- |
| GetandSet                 | Assign and retrieve label attributes          | Values match inputs                       | PASSED    |
| ConstructorInit           | Initialize label using constructor            | Values match constructor parameters       | PASSED    |
| ProjectAssignment         | Assign project pointer to label               | Project pointer stored correctly          | PASSED    |

### Technical Implementation
```
// Example unit test
ScaleLabel label;

label.setName("High Impact");
label.setId(69);
label.setLevel(5);
label.setType(1);

EXPECT_EQ(label.getName(), "High Impact");
EXPECT_EQ(label.getId(), 69);
EXPECT_EQ(label.getLevel(), 5);
EXPECT_EQ(label.getType(), 1);
```

### Execution Log
[==========] Running 3 tests from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 3 tests from ScaleLabelUnitTest.<br>
[RUN       ] ScaleLabelUnitTest.GetandSet<br>
[        OK] ScaleLabelUnitTest.GetandSet<br>
[RUN       ] ScaleLabelUnitTest.ConstructorInit<br>
[        OK] ScaleLabelUnitTest.ConstructorInit<br>
[RUN       ] ScaleLabelUnitTest.ProjectAssignment<br>
[        OK] ScaleLabelUnitTest.ProjectAssignment<br>
[----------] 3 tests from ScaleLabelUnitTest <br>

[  PASSED  ] 3 tests.
