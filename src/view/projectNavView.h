#ifndef PROJECT_NAV_VIEW_H
#define PROJECT_NAV_VIEW_H


#include "projectModel.h"
#include "riskItemModel.h"
#include "riskExportView.h"
#include "riskManagerModel.h"


#include <vector>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class projectNavView : public Wt::WContainerWidget {
public:
    projectNavView(Project project, std::vector<RiskItem> risks, std::shared_ptr<RiskManager> riskManager);
    Wt::WPushButton* getBackBtn() const { return backBtn; }

private:
    void buildNavProj();
    void setActive(Wt::WPushButton* btn);
    // added for integration NG
    void showRisks();

    Project project_;
    std::vector<RiskItem> risks_;
    std::shared_ptr<RiskManager> riskManager_;
    // end added for integration
    

    Wt::WContainerWidget* contentArea_;
    Wt::WPushButton* activeBtn;
    Wt::WPushButton* backBtn;
    //Wt::WPushButton* viewBtn;
    Wt::WPushButton* riskBtn;
    // Wt::WPushButton* editBtn;
    Wt::WPushButton* matrixBtn;
    Wt::WPushButton* exportBtn;
    std::shared_ptr<RiskExportView> exportResource_;
};

#endif
