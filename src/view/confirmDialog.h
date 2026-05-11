#pragma once

//
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <functional>

class ConfirmDialog : public Wt::WContainerWidget
{
public:
    ConfirmDialog(const std::string& title,
                  const std::string& message,
                  std::function<void()> onYes);

private:
    Wt::WPushButton* yesBtn;
    Wt::WPushButton* noBtn;

    void buildDialog(const std::string& title,
                     const std::string& message,
                     std::function<void()> onYes);
};
