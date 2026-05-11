#ifndef RISK_EDIT_FORM_H
#define RISK_EDIT_FORM_H

#include <functional>
#include <string>

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>
#include <Wt/WComboBox.h>
#include "../model/riskManagerModel.h"

class RiskEditForm : public Wt::WContainerWidget {
public:
    RiskEditForm(std::shared_ptr<RiskManager> riskManager,
        int riskID,
        const std::string &name,
        const std::string &desc,
        int probability,
        int impact,
        std::function<void()> onSave);

private:
    void buildForm();
    Wt::WLineEdit* idInput;
    Wt::WTextArea* descInput;
    Wt::WComboBox* likeCombo;
    Wt::WComboBox* impactCombo;

    std::shared_ptr<RiskManager> riskManager_;
    std::function<void()> onSave_;

    int riskID_;
    std::string name_;
    std::string desc_;
    int probability_;
    int impact_;
};

#endif