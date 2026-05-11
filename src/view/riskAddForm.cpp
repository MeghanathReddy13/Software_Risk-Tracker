#include "riskAddForm.h"
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <memory>

using namespace std;

RiskAddForm::RiskAddForm(std::shared_ptr<RiskManager> riskManager,
    int projectID,
    std::function<void()> onSave)
    : Wt::WContainerWidget(),
    riskManager_(riskManager),
    projectID_(projectID),
    onSave_(onSave)
{
    this->addStyleClass("content-display"); 
    buildForm();
}

void RiskAddForm::buildForm() {
    auto title = addWidget(make_unique<Wt::WText>("Project-1"));
    title->addStyleClass("project-title-header"); 

    auto wrapper = addWidget(make_unique<Wt::WContainerWidget>());
    wrapper->addStyleClass("form-grid-wrapper"); 

    auto leftCol = wrapper->addWidget(make_unique<Wt::WContainerWidget>());
    leftCol->addStyleClass("form-column");

    auto idCard = leftCol->addWidget(make_unique<Wt::WContainerWidget>());
    idCard->addStyleClass("input-card");
    idCard->addWidget(make_unique<Wt::WText>("Risk Identifier"))->addStyleClass("card-label");
    idInput = idCard->addWidget(make_unique<Wt::WLineEdit>());
    idInput->addStyleClass("form-input-field");

    auto descCard = leftCol->addWidget(make_unique<Wt::WContainerWidget>());
    descCard->addStyleClass("input-card");
    descCard->addWidget(make_unique<Wt::WText>("Risk Description"))->addStyleClass("card-label");
    descInput = descCard->addWidget(make_unique<Wt::WTextArea>());
    descInput->addStyleClass("form-input-field");

    auto rightCol = wrapper->addWidget(make_unique<Wt::WContainerWidget>());
    rightCol->addStyleClass("form-column");

    auto likeCard = rightCol->addWidget(make_unique<Wt::WContainerWidget>());
    likeCard->addStyleClass("input-card");
    likeCard->addWidget(make_unique<Wt::WText>("Risk Likelihood"))->addStyleClass("card-label");
    likeCombo = likeCard->addWidget(make_unique<Wt::WComboBox>());
    likeCombo->addStyleClass("form-input-field");
    likeCombo->addItem("1"); 
    likeCombo->addItem("2"); 
    likeCombo->addItem("3"); 
    likeCombo->addItem("4"); 
    likeCombo->addItem("5");

    impactCard = rightCol->addWidget(make_unique<Wt::WContainerWidget>());
    impactCard->addStyleClass("input-card");
    impactCard->addWidget(make_unique<Wt::WText>("Risk Impact"))->addStyleClass("card-label");
    impactCombo = impactCard->addWidget(make_unique<Wt::WComboBox>());
    impactCombo->addStyleClass("form-input-field");
    impactCombo->addItem("1"); 
    impactCombo->addItem("2"); 
    impactCombo->addItem("3"); 
    impactCombo->addItem("4");
    impactCombo->addItem("5");

    auto saveBtn = addWidget(make_unique<Wt::WPushButton>("Add Risk"));
    saveBtn->addStyleClass("save-edit-btn");
    saveBtn->clicked().connect([this]() {
        if (!riskManager_) {
            return;
        }

        std::string riskName = idInput->text().toUTF8();
        std::string desc = descInput->text().toUTF8();
        int probability = std::stoi(likeCombo->currentText().toUTF8());
        int impact = std::stoi(impactCombo->currentText().toUTF8());

        riskManager_->addRisk(projectID_, riskName, desc, probability, impact);
        if (onSave_) {
            onSave_();
        }
    });
}