#include "riskEditForm.h"
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <memory>

using namespace std;

RiskEditForm::RiskEditForm(std::shared_ptr<RiskManager> riskManager,
    int riskID,
    const std::string &name,
    const std::string &desc,
    int probability,
    int impact,
    std::function<void()> onSave) 
: Wt::WContainerWidget(),
    riskManager_(riskManager),
    onSave_(onSave),
    riskID_(riskID),
    name_(name),
    desc_(desc),
    probability_(probability),
    impact_(impact) {
    this->addStyleClass("content-display"); 
    buildForm();
}

void RiskEditForm::buildForm() {

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
    idInput->setText(std::to_string(riskID_));


    auto descCard = leftCol->addWidget(make_unique<Wt::WContainerWidget>());
    descCard->addStyleClass("input-card");
    descCard->addWidget(make_unique<Wt::WText>("Risk Description"))->addStyleClass("card-label");

    descInput = descCard->addWidget(make_unique<Wt::WTextArea>());
    descInput->addStyleClass("form-input-field");
    descInput->setText(desc_);

    auto rightCol = wrapper->addWidget(make_unique<Wt::WContainerWidget>());
    rightCol->addStyleClass("form-column");


    auto likeCard = rightCol->addWidget(make_unique<Wt::WContainerWidget>());
    likeCard->addStyleClass("input-card");
    likeCard->addWidget(make_unique<Wt::WText>("Risk Likelihood"))->addStyleClass("card-label");
   
    //removed the auto so combo box is not local
    /* auto */ likeCombo = likeCard->addWidget(make_unique<Wt::WComboBox>());
    likeCombo->addStyleClass("form-input-field");
    likeCombo->addItem("1"); 
    likeCombo->addItem("2"); 
    likeCombo->addItem("3"); 
    likeCombo->addItem("4");
    likeCombo->addItem("5");
    likeCombo->setCurrentIndex(probability_ -1);

    // same issue for impact combo
    auto impactCard = rightCol->addWidget(make_unique<Wt::WContainerWidget>());
    impactCard->addStyleClass("input-card");
    impactCard->addWidget(make_unique<Wt::WText>("Risk Impact"))->addStyleClass("card-label");
    
    /* auto */ impactCombo = impactCard->addWidget(make_unique<Wt::WComboBox>());
    impactCombo->addStyleClass("form-input-field");
    impactCombo->addItem("1");
    impactCombo->addItem("2");
    impactCombo->addItem("3"); 
    impactCombo->addItem("4");
    impactCombo->addItem("5");
    impactCombo->setCurrentIndex(impact_ - 1);


    auto saveBtn = addWidget(make_unique<Wt::WPushButton>("Save Edit"));
    saveBtn->addStyleClass("save-edit-btn"); 
    // connect the click to it NG
    saveBtn->clicked().connect([this]() {
        int id = std::stoi(idInput->text().toUTF8());
        std::string desc = descInput->text().toUTF8();
        int likelihood = std::stoi(likeCombo->currentText().toUTF8());
        int impact = std::stoi(impactCombo->currentText().toUTF8());

        riskManager_->updateRisk(id, desc, likelihood, impact);
        if (onSave_) {
            onSave_();
        }
    });
}