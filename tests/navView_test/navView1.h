#ifndef NAVVIEW_H
#define NAVVIEW_H

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>


class navView:public Wt::WApplication{

public:
	navView(const Wt::WEnvironment& env);

private:
	Wt::WContainerWidget* shell_;
	Wt::WLineEdit* searchBar_;
        Wt::WContainerWidget* contentArea_;

	void addStyles();
	void buildUI();
};

#endif


