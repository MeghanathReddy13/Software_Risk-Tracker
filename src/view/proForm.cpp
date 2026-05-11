#include "proForm.h"
#include "projectManagerModel.h"
#include <chrono>

ProjectForm::ProjectForm(ProjectManager* pm, std::function<void()> onSave)
    : pm_(pm), onSave_(onSave), editMode_(false)
{
    formCard = addWidget(std::make_unique<Wt::WContainerWidget>());
    formCard->addStyleClass("form-card");
    buildForm();
}

ProjectForm::ProjectForm(ProjectManager* pm, std::function<void()> onSave, Project existing)
    : pm_(pm), onSave_(onSave), project_(existing), editMode_(true)
{
    formCard = addWidget(std::make_unique<Wt::WContainerWidget>());
    formCard->addStyleClass("form-card");
    buildForm();
}

void ProjectForm::buildForm()
{
    auto prefixText = formCard->addWidget(
        std::make_unique<Wt::WText>("Software Risk Tracker"));
    prefixText->addStyleClass("prefix-text");

    title = formCard->addWidget(
        std::make_unique<Wt::WText>(editMode_ ? "Edit Project" : "Create Project"));
    title->addStyleClass("form-title");

    formCard->addWidget(std::make_unique<Wt::WText>("Project Name"));
    projectName = formCard->addWidget(std::make_unique<Wt::WLineEdit>());
    projectName->setPlaceholderText("Enter project name");

    formCard->addWidget(std::make_unique<Wt::WText>("Number of Risks"));
    likelinessCount = formCard->addWidget(std::make_unique<Wt::WSpinBox>());
    likelinessCount->setMinimum(1);
    likelinessCount->setMaximum(10);

/*    formCard->addWidget(std::make_unique<Wt::WText>("Number of Risk Impacts"));
    impactCount = formCard->addWidget(std::make_unique<Wt::WSpinBox>());
    impactCount->setMinimum(1);
    impactCount->setMaximum(10);
*/ //Removing this feature
    if (editMode_) {
        projectName->setText(project_.getName());
        likelinessCount->setValue(project_.getProbCount());
    //    impactCount->setValue(project_.getImpactCount());
    }

    submitButton = formCard->addWidget(
        std::make_unique<Wt::WPushButton>(editMode_ ? "Save Edit" : "Create Project"));
    submitButton->clicked().connect([this] { handleSubmit(); });

    if (editMode_) {
        auto cancelBtn = formCard->addWidget(
            std::make_unique<Wt::WPushButton>("Cancel"));
        cancelBtn->clicked().connect([this] { onSave_(); });
    }
}

void ProjectForm::handleSubmit()
{
    std::string name = projectName->text().toUTF8();
    if (name.empty()) return;

    int likeliness = likelinessCount->value();
//    int impacts    = impactCount->value();

    if (editMode_) {
        project_.setName(name);
        project_.setProbCount(likeliness);
  //      project_.setImpactCount(impacts);
        project_.setModified(std::chrono::system_clock::now());
        pm_->updateProject(project_);
    } else {
        Project p;
        p.setName(name);
        p.setProbCount(likeliness);
    //    p.setImpactCount(impacts);
        p.setCreated(std::chrono::system_clock::now());
        p.setModified(std::chrono::system_clock::now());
        pm_->addProject(p);
    }

    onSave_();
}
