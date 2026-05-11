# pragma once

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

class riskTrackerApp;

class navView:public Wt::WContainerWidget{

public:
	navView(riskTrackerApp* app);

private:
        riskTrackerApp* app_;
	Wt::WContainerWidget* shell_;
        Wt::WContainerWidget* contentArea_;
        
//tab buttons
        Wt::WPushButton* selectBtn;
        Wt::WPushButton* createBtn;
        Wt::WPushButton* userBtn;
//active tab point
        Wt::WPushButton* activeBtn;

	void buildUI();
        void setActive(Wt::WPushButton* btn);
        void loadUsers(Wt::WContainerWidget* listContainer);
        void showProjects();
};

