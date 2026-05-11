#include "navView.h"
#include "proForm.h"
#include "createUser.h"
#include "confirmDialog.h"
#include "riskTrackerApp.h"
#include "riskManagerModel.h"
#include "projectManagerModel.h"
#include "userManagerModel.h"
#include "projectNavView.h"


#include <Wt/WText.h>
#include <Wt/WAnchor.h>
#include <Wt/WEnvironment.h>
#include <Wt/WLength.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WPushButton.h>

#include <Wt/WComboBox.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <memory>
#include <utility>

using namespace std;
/*--------------ACTIVE TAB FUNCTION----------------*/
void navView::setActive(Wt::WPushButton* btn)
{
	if(activeBtn !=nullptr) {
		activeBtn->removeStyleClass("active");
	}

	activeBtn = btn;

	if (activeBtn!=nullptr){
		activeBtn->addStyleClass("active");
	}
}
/*-----------CONSTRUCTOR-------------*/
navView::navView(riskTrackerApp* app)
	: 
	app_(app),
	shell_(nullptr),
	contentArea_(nullptr),
	selectBtn(nullptr),
	createBtn(nullptr),
	userBtn(nullptr),
	activeBtn(nullptr)
{
// global CSS file load up
// useStyleSheet("style.css")
	buildUI();
}

void navView::buildUI()
/* -------------MAIN SHELL----------------*/
{
	shell_=addWidget(make_unique<Wt::WContainerWidget>());
	shell_->addStyleClass("shell");

/* ------------- TOP BAR ----------------*/

auto topbar = shell_->addWidget(make_unique<Wt::WContainerWidget>());
topbar->addStyleClass("topbar");

auto topLayout = topbar->setLayout(make_unique<Wt::WHBoxLayout>());

auto brand = make_unique<Wt::WText>("SOFTWARE RISK TRACKER");
brand->addStyleClass("brand");

auto logout = make_unique<Wt::WPushButton>("Logout");
logout->addStyleClass("logoutBtn");
logout->clicked().connect([this]() {
	app_->logout();
});

topLayout->addWidget(std::move(brand),0, Wt::AlignmentFlag::Left);
topLayout->addStretch(1);
topLayout->addWidget(std::move(logout), 0, Wt::AlignmentFlag::Right);

/* --------------- TABS -----------------*/

auto tabs = shell_->addWidget(make_unique<Wt::WContainerWidget>());
tabs->addStyleClass("tabs");

selectBtn = tabs->addWidget(make_unique<Wt::WPushButton>("Select Project"));
selectBtn->addStyleClass("tabBtn");//default active

createBtn = tabs->addWidget(make_unique<Wt::WPushButton>("Create Project"));
createBtn->addStyleClass("tabBtn");

userBtn =  tabs->addWidget(make_unique<Wt::WPushButton>("Users"));
userBtn->addStyleClass("tabBtn");

/*default active tab*/
setActive(selectBtn);


/* --------- CONTENT AREA ----------*/

contentArea_ = shell_->addWidget(make_unique<Wt::WContainerWidget>());

/*--------------- BUTTON CONNECTIONS -----------------*/

showProjects();  

selectBtn->clicked().connect([this]() {
	setActive(selectBtn);
	contentArea_->clear();
	showProjects();  

});

createBtn->clicked().connect([this](){
	setActive(createBtn);

	contentArea_->clear();
	contentArea_->addWidget(make_unique<ProjectForm>(
		app_->getProjectManager().get(),
		[this]() {
			setActive(selectBtn);
			contentArea_->clear();
			showProjects();
		}
	));
});

userBtn->clicked().connect([=, this](){
	setActive(userBtn);
	
	contentArea_->clear();

	//create a container for users view
	auto usersContainer = contentArea_->addWidget(
		make_unique<Wt::WContainerWidget>());
	
	auto title = usersContainer->addWidget(std::make_unique<Wt::WText>("User Management"));
	title->addStyleClass("form-title");
	
	auto formContainer = usersContainer->addWidget(
	make_unique<Wt::WContainerWidget>());
	formContainer->hide();
	
	auto createUserBtn = usersContainer->addWidget(
		make_unique<Wt::WPushButton>("Create User"));
	createUserBtn->addStyleClass("tabBtn");

	auto listContainer = usersContainer->addWidget(
	make_unique<Wt::WContainerWidget>());

	auto header = listContainer->addWidget(
		std::make_unique<Wt::WContainerWidget>());

	auto headerLayout = header->setLayout(
		std::make_unique<Wt::WHBoxLayout>());

	headerLayout->addWidget(std::make_unique<Wt::WText>("Name"), 1);

	headerLayout->addWidget(std::make_unique<Wt::WText>("email"), 2);
	headerLayout->addWidget(std::make_unique<Wt::WText>("Role"), 1);
	loadUsers(listContainer);

	//connect action later
	createUserBtn->clicked().connect([this, listContainer, formContainer, createUserBtn]() {
		createUserBtn->hide();
		listContainer->hide();
		formContainer->show();
		formContainer->clear();

		auto form = formContainer->addWidget(make_unique<CreateUserForm>());
		
		form->onUserCreated = [this, listContainer, formContainer, createUserBtn](std::string name,std::string email,std::string password, std::string role){
		
		auto app = dynamic_cast<riskTrackerApp*>(Wt::WApplication::instance());
		if(!app) return;
		
		auto userManager = app->getUserManager();
		if(!userManager->createUser(name, email, password, role)) {
			std::cout << "User Creation Failed\n";
			return;
		}
		formContainer->hide();
		listContainer->show();
		createUserBtn->show();
		listContainer->clear();

		auto header = listContainer->addWidget(
		std::make_unique<Wt::WContainerWidget>());
		
		auto headerLayout = header->setLayout(
		std::make_unique<Wt::WHBoxLayout>());
		
		headerLayout->addWidget(std::make_unique<Wt::WText>("Name"),1);
		headerLayout->addWidget(std::make_unique<Wt::WText>("Email"),2);
		headerLayout->addWidget(std::make_unique<Wt::WText>("Role"),1);

		loadUsers(listContainer);

		};
	});
});
}
void navView::loadUsers(Wt::WContainerWidget* listContainer)
{
	auto app = dynamic_cast<riskTrackerApp*>(Wt::WApplication::instance());
	if(!app) return;
	auto userManager = app->getUserManager();
	auto users = app->getDatabaseManager()->getAllUsers();

	for(const auto& user : users){
		auto row = listContainer->addWidget(std::make_unique<Wt::WContainerWidget>());
		row->addStyleClass("user-row");
		auto layout = row->setLayout(std::make_unique<Wt::WHBoxLayout>());

		layout->addWidget(std::make_unique<Wt::WText>(user.getName()), 2);
		layout->addWidget(std::make_unique<Wt::WText>(user.getUserName()), 3);
		auto roles = user.getRole();
		std::string roleStr = roles.empty() ? "": roles[0];
		layout->addWidget(std::make_unique<Wt::WText>(roleStr), 2);
		auto btnContainer  = layout->addWidget(std::make_unique<Wt::WContainerWidget>(), 2);
		std::cout<<"ui user id : " <<user.getID() << std::endl; 	
		auto btnLayout = btnContainer->setLayout(std::make_unique<Wt::WHBoxLayout>());
		if(userManager && userManager->isAdmin()){
			auto editBtn = btnLayout->addWidget(std::make_unique<Wt::WPushButton>("Edit"));
			editBtn->addStyleClass("edit-btn");
			editBtn->clicked().connect([this, user, listContainer]{
			auto app = dynamic_cast<riskTrackerApp*>(Wt::WApplication::instance());
			if(!app)return;

			auto parent = listContainer ->parent();
			
			auto formContainer = dynamic_cast<Wt::WContainerWidget*>(parent->children()[1]);

			auto createUserBtn = dynamic_cast<Wt::WPushButton*>(parent->children()[2]);
			createUserBtn->hide();
			listContainer->hide();
			formContainer->show();
			formContainer->clear();
			std::cout<<"edit clicked\n";
			
			auto form = formContainer->addWidget(std::make_unique<Wt::WContainerWidget>());
			form->addStyleClass("form-card");

			form->addWidget(std::make_unique<Wt::WText>("Name"));
			auto nameEdit = form->addWidget(std::make_unique<Wt::WLineEdit>(user.getName()));

			auto roleEdit = form->addWidget(std::make_unique<Wt::WLineEdit>(
			user.getRole().empty() ? "" :user.getRole()[0]));

			auto emailEdit = form->addWidget(std::make_unique<Wt::WLineEdit>(user.getUserName()));

			auto passwordEdit = form ->addWidget(std::make_unique<Wt::WLineEdit>());
			passwordEdit->setPlaceholderText("New Password( leave black to keep same)");
			auto btnRow = form->addWidget( std::make_unique<Wt::WContainerWidget>());
			auto btnLayout = btnRow->setLayout(std::make_unique<Wt::WHBoxLayout>());
			auto saveBtn = btnLayout->addWidget(std::make_unique<Wt::WPushButton>("Save"));
			auto cancelBtn = btnLayout->addWidget(std::make_unique<Wt::WPushButton>("Cancel"));
			cancelBtn->clicked().connect([listContainer, formContainer, createUserBtn]{
				formContainer->hide();
				listContainer->show();
				createUserBtn->show();
			});

			saveBtn->clicked().connect([this, user, nameEdit, roleEdit,emailEdit, passwordEdit, listContainer, formContainer, createUserBtn]{

			auto app = dynamic_cast<riskTrackerApp*>(Wt::WApplication::instance());
		if(!app) return;

		auto userManager = app->getUserManager();
		
		std::string newName = nameEdit->text().toUTF8();
		std::string newRole = roleEdit->text().toUTF8();
		std::string newEmail = emailEdit->text().toUTF8();
		std::string newPassword = passwordEdit->text().toUTF8();

		if(userManager->editUser(user.getID(), newName, newEmail, newPassword, newRole)){
			std::cout<<"User updated\n";
			formContainer->hide();
			listContainer->show();
			createUserBtn->show();
			listContainer->clear();
			loadUsers(listContainer);
		}

		else {
			std::cout <<"update failed\n";
		}
	});
	});
//DELETE USER BUTTON
	auto deleteBtn = btnLayout->addWidget(std::make_unique<Wt::WPushButton>("Delete"));
	deleteBtn->addStyleClass("delete-Btn");
	deleteBtn->clicked().connect([this,user, listContainer]{
		auto app = dynamic_cast<riskTrackerApp*>(Wt::WApplication::instance());
		std::cout <<"delete clicked\n";
		if(!app) return;
		auto userManager = app->getUserManager();
		if(user.getID()==userManager->getCurrentUser().getID()){
			std::cout << "Cannot delete current user\n";
			return;
		}
		//show confirmation
		Wt::WApplication::instance()->root()->addWidget(
			std::make_unique<ConfirmDialog>(
			"Delete User",
			"Are you sure you want to delete\""+user.getName()+"\"?",
			[this, user, listContainer](){
				auto app = dynamic_cast<riskTrackerApp*>(Wt::WApplication::instance());
				if(!app) return;
				auto userManager = app->getUserManager();
				if(userManager->deleteUser(user.getID())) {
					std::cout << "User deleted\n";
					listContainer->clear();
					loadUsers(listContainer);
				}else {
					std::cout<<"Deleted failed\n";
				}
			}
	)

	);

	});
}
}
}
/*-------------- SHOW PROJECTS ---------------*/
void navView::showProjects()
{
	contentArea_->clear();

	// header
	auto header = contentArea_->addWidget(make_unique<Wt::WContainerWidget>());
	header->addStyleClass("project-list-header");
	header->addWidget(make_unique<Wt::WText>("Select Project"))->addStyleClass("project-list-title");
	header->addWidget(make_unique<Wt::WBreak>());
	header->addWidget(make_unique<Wt::WText>("Choose a project to manage"))->addStyleClass("project-list-subtitle");

	auto projects = app_->getProjectManager()->getAllProjects();

	for (Project p : projects) {
		auto row = contentArea_->addWidget(make_unique<Wt::WContainerWidget>());
		row->addStyleClass("project-row");

		auto info = row->addWidget(make_unique<Wt::WContainerWidget>());
		info->addStyleClass("project-info");
		info->addWidget(make_unique<Wt::WText>(p.getName()))->addStyleClass("project-name");
		info->addWidget(make_unique<Wt::WBreak>());
		info->addWidget(make_unique<Wt::WText>(
			"Number of Risks: " + to_string(p.getProbCount()) 
//			"  Impact: " + to_string(p.getImpactCount())
		))->addStyleClass("project-meta");

		auto drop = row->addWidget(make_unique<Wt::WComboBox>());
		drop->addItem("Select an option");
		drop->addItem("Edit");
		drop->addItem("Delete");
		//drop->addItem("Export");
		drop->addItem("Use");
		drop->addStyleClass("project-dropdown");

		drop->changed().connect([drop, p, this]() mutable {
			int idx = drop->currentIndex();
			drop->setCurrentIndex(0);

			if (idx == 1) { // Edit
				setActive(createBtn);
				contentArea_->clear();
				contentArea_->addWidget(make_unique<ProjectForm>(
					app_->getProjectManager().get(),
					[this]() {
						setActive(selectBtn);
						contentArea_->clear();
						showProjects();
					},
					p
				));
			} else if (idx == 2) { // Delete
				Wt::WApplication::instance()->root()->addWidget(make_unique<ConfirmDialog>(
					"Delete Project",
					"Are you sure you want to delete \"" + p.getName() + "\"?",
					[this, p]() mutable {
						app_->getProjectManager()->deleteProject(p);
						showProjects();
					}
				));
			} else if(idx == 3) {
				contentArea_->clear();

				int projectID = p.getID();

				auto risks = app_->getRiskManager()->listRisks(projectID);

				auto projectView = contentArea_->addWidget(
					make_unique<projectNavView>(p, risks, app_->getRiskManager()));


                //projectView->getBackBtn()->clicked().connect([this]() {
					//contentArea_->clear();
                    //showProjects(); 
					//setActive(selectBtn);
				//auto projectView = contentArea_->addWidget(make_unique<projectNavView>());

                projectView->getBackBtn()->clicked().connect([this]() {
					contentArea_->clear();
                    showProjects(); 
					setActive(selectBtn);
				});	
			}
		});
	}

	if (projects.empty()) {
		contentArea_->addWidget(
			make_unique<Wt::WText>("No projects yet. Click 'Create Project' to add one.")
		)->addStyleClass("project-meta");
	}
}
