#ifndef PROJECTFORM_H
#define PROJECTFORM_H

#include <functional>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WSpinBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "projectModel.h"

class ProjectManager;

class ProjectForm : public Wt::WContainerWidget
{
public:
    // Create mode
    ProjectForm(ProjectManager* pm, std::function<void()> onSave);
    // Edit mode
    ProjectForm(ProjectManager* pm, std::function<void()> onSave, Project existing);

private:
    ProjectManager* pm_;
    std::function<void()> onSave_;
    Project project_;
    bool editMode_;

    Wt::WContainerWidget* formCard;
    Wt::WText* title;
    Wt::WLineEdit* projectName;
    Wt::WSpinBox* likelinessCount;
   //  Wt::WSpinBox* impactCount;
    Wt::WPushButton* submitButton;

    void buildForm();
    void handleSubmit();
};

#endif 
