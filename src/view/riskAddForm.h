#ifndef RISK_ADD_FORM_H
#define RISK_ADD_FORM_H

// allows passing functions as objects
#include <functional>

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>
#include <Wt/WComboBox.h>

#include "../model/riskManagerModel.h"

class RiskAddForm : public Wt::WContainerWidget {
public:
    RiskAddForm(std::shared_ptr<RiskManager> riskManager,
        int projectID,
        std::function<void()> onSave);

private:
    void buildForm();
    std::shared_ptr<RiskManager> riskManager_;
    int projectID_;
    std::function<void()> onSave_;
    
    Wt::WContainerWidget* impactCard;
    Wt::WLineEdit* idInput;
    Wt::WTextArea* descInput;
    Wt::WComboBox* likeCombo;
    Wt::WComboBox* impactCombo; 
};

#endif