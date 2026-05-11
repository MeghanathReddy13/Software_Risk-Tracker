#include "navView.cpp"
#include "proForm.h"

#include <Wt/WText.h>
#include <Wt/WAnchor.h>
#include <Wt/WEnvironment.h>
#include <Wt/WLength.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WPushButton.h>

#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <memory>
#include <utility>

using namespace std;

navView::navView(const Wt::WEnvironment& env)
	: Wt::WApplication(env),
	shell_(nullptr),
	searchBar_(nullptr)
{
	setTitle("Software Risk Tracker");

	addStyles();
	buildUI();
}

void navView::addStyles()
{
	root()->addWidget(make_unique<Wt::WText>(R"(
<style>
	body{ 
	margin:0 !important;
	background:#f6f7fb !important;
	font-family: Arial, Helvetica, sans-serif !important;
	}

	.shell{
	max-width: 980px !important;
	margin:18px auto !important;
	background: #ffffff !important;
	border: 1px solid #cfcfcf !important;
	border-radius: 6px !important;
	overflow:hidden !important;
	}

/*top header*/
	.topbar{
	padding: 10px 14px !important;
	border-bottom:1px solid #cfcfcf !important;
	background: #f1f1f1 !important;
	}

	.brand{
	font-weight:800 !important;
	font-size: 20px !important;
	color:#111;
	}

	.logOut{
	background-color: #c95647;
	color: #fcfcfc;
	border:none;
	padding: 6px 14px;
	border-radius:7px;
	font-size: 16px;
	cursor:pointer;
	}
	
	.logOut:hover{
	background-color: #e68a7e;
	}
/*Nav link row*/

	.tabs{
	padding: 8px 14px !important;
	border-bottom: 1px solid #d1d5db !important;
	background: #ffffff !important;
	}

	a.tab, a.tab:visited{
	color: #111 !important;
	text-decoration: none !important;
	font-size: 16px !important;
	margin-right: 35px !important;

	}

	a.tab:hover{
	text-decoration: underline !important;
	}

	a.tab active{
	color:#0b63d1 !important;
	font-weight: 700 !important;
	text-decoration: underline !improtant;
	}

/* search bar under nav*/

	.search wrap{
	padding: 12px 14px 14px !important;
	background: #ffffff !important;
	}

	input.search{
	width: 460px !important;
	border: 1px solid #cbd5e1 !important;
	border-radius: 4px !important;
	padding: 6px 8px !important;
	font-size:16px !important;
	}

	.hint{i
	color:#222 !important;
	font-size:15px !important;
	margin-top:8px !important;
	}
</style>
	)"));
}

void navView::buildUI()
{
	shell_=root()->addWidget(make_unique<Wt::WContainerWidget>());
shell_->addStyleClass("shell");

/* ------------- TOP BAR ----------------*/

auto topbar = shell_->addWidget(make_unique<Wt::WContainerWidget>());
topbar->addStyleClass("topbar");

auto topLayout = topbar->setLayout(make_unique<Wt::WHBoxLayout>());

auto brand = make_unique<Wt::WText>("SOFTWARE RISK TRACKER");
brand->addStyleClass("brand");

auto logout = make_unique<Wt::WPushButton>("Logout");
logout->addStyleClass("logoutBtn");

topLayout->addWidget(std::move(brand),0, Wt::AlignmentFlag::Left);
topLayout->addStretch(1);
topLayout->addWidget(std::move(logout), 0, Wt::AlignmentFlag::Right);

/* --------------- TABS -----------------*/

auto tabs = shell_->addWidget(make_unique<Wt::WContainerWidget>());
tabs->addStyleClass("tabs");

auto selectBtn = tabs->addWidget(make_unique<Wt::WPushButton>("Select Project"));
selectBtn->addStyleClass("tabBtn");

auto createBtn = tabs->addWidget(make_unique<Wt::WPushButton>("Create Project"));
selectBtn->addStyleClass("tabBtn");

auto deleteBtn = tabs->addWidget(make_unique<Wt::WPushButton>("Delete Project"));
selectBtn->addStyleClass("tabBtn");

/* ------------- Search --------------*/
auto searchWrap = shell_->addWidget(make_unique<Wt::WContainerWidget>());
searchWrap->addStyleClass("searchWrap");

searchBar_=searchWrap-> addWidget(make_unique<Wt::WLineEdit>());
searchBar_->addStyleClass("Search");
searchBar_->setPlaceholderText("Search project...");

auto hint = searchWrap->addWidget(make_unique<Wt::WText>( "tip: type part of project name like alpha or 2"));
hint->setStyleClass("hint");

/* --------- CONTENT AREA ----------*/

contentArea_ = shell_-> addWidget(make_unique<Wt::WContainerWidget>());

/*--------------- BUTTON CONNECTIONS -----------------*/

creayBtn->clicked().connect([=](){
	conetctArea_->clear();
	contentArea_->addWidget(make_unique<ProjectForm>());
});

slectBtn->clicked().connect([=](){
	contentArea_->clear();
});

deleteBtn->clicked().connect([=](){
	contentArea_->clear();
});
}
}



