#include "confirmDialog.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>

/*-----------CONSTRUCTOR-------------*/
ConfirmDialog::ConfirmDialog(const std::string& title,
                             const std::string& message,
                             std::function<void()> onYes)
    : yesBtn(nullptr),
      noBtn(nullptr)
{
    addStyleClass("confirm-overlay");
    buildDialog(title, message, onYes);
}

/*-----------BUILD DIALOG-------------*/
void ConfirmDialog::buildDialog(const std::string& title,
                                const std::string& message,
                                std::function<void()> onYes)
{
    auto box = addWidget(std::make_unique<Wt::WContainerWidget>());
    box->addStyleClass("confirm-box");

    // Title
    auto titleText = box->addWidget(std::make_unique<Wt::WText>(title));
    titleText->addStyleClass("confirm-title");

    // Message
    auto msgText = box->addWidget(std::make_unique<Wt::WText>(message));
    msgText->addStyleClass("confirm-message");

    // Button row
    auto btnRow = box->addWidget(std::make_unique<Wt::WContainerWidget>());
    btnRow->addStyleClass("confirm-btns");

    yesBtn = btnRow->addWidget(std::make_unique<Wt::WPushButton>("Yes"));
    yesBtn->addStyleClass("confirm-yes");

    noBtn = btnRow->addWidget(std::make_unique<Wt::WPushButton>("No"));
    noBtn->addStyleClass("confirm-no");

    /*--------- BUTTON CONNECTIONS ---------*/

    yesBtn->clicked().connect([this, onYes]() {
        onYes();
        removeFromParent();
    });

    noBtn->clicked().connect([this]() {
        removeFromParent();
    });
}
