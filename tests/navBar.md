# Navigation Bar Assement
### Risk Tracker
### Date: 3/4/2026

## Components:
* view: navView1.h, navView1.cpp
* modle: projectForm (via proForm.h)
* verifier: navView_test

### Tracebility Matrix
|  Requirement     |  Implementation             |  Verified By                    |  
|------------------|-----------------------------|---------------------------------|
|Dynamic Navigation|contentArea_->addWidget()    |NavUITest.SwitchToCreateProject  |
|View Clearing     |contentArea_->clear()        |NavUITest.ClearAreaOnTabSwitch   |
|UI Constraints    |shell->addStyleClass("shell")|Visual Inspection / CSSValidation|
|Search Readiness  |searchBar_ instantiation     |NavUITest.SearchBarPresence      |

### Test Results

|   Test Case Name    |            Scenario            |      Expected Result                     |Status|
|---------------------|--------------------------------|------------------------------------------|------|
|SwitchToCreateProject|Click "Create Project" button   |contentArea contains ProjectForm          |PASSED|
|ClearAreaOnTabSwitch |Switch from "Create" to "Select"|contentArea is emptied                    |PASSED|
|SearchBarPresence    |Initialize navView              |searchBar_ is not null and has placeholder|PASSED|
|LogOutAction         |Click "Logout" button           |Session terminates / Redirect             |PASSED|

### Technical Implementation
~~~
// Logic flow inside navView1.cpp for dynamic view switching
createBtn->clicked().connect([=](){
    contentArea_->clear(); 
    contentArea_->addWidget(make_unique<ProjectForm>());
});
root()->addWidget(make_unique<Wt::WText>(R"(
    .brand { font-weight:800; font-size: 20px; color:#111; }
    .shell { max-width: 980px; margin:18px auto; })")
);
~~~
### Execution Log
~~~
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from navView_test
[ RUN      ] NavUITest.SwitchToCreateProject
[       OK ] NavUITest.SwitchToCreateProject (4 ms)
[ RUN      ] NavUITest.ClearAreaOnTabSwitch
[       OK ] NavUITest.ClearAreaOnTabSwitch (2 ms)
[ RUN      ] NavUITest.SearchBarPresence
[       OK ] NavUITest.SearchBarPresence (1 ms)
[ RUN      ] NavUITest.LogOutAction
[       OK ] NavUITest.LogOutAction (3 ms)
[----------] 4 tests from NavUITest (10 ms total)

[  PASSED  ] 4 tests.
~~~
