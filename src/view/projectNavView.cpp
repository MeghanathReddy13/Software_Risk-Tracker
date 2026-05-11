#include "projectNavView.h"
#include "riskMatrixView.h"
#include "riskAddForm.h"
#include "riskView.h"
#include "riskExportView.h"

#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <vector>

using namespace std;


void projectNavView::setActive(Wt::WPushButton* btn)
{
    if (activeBtn != nullptr) {
        activeBtn->removeStyleClass("nav-btn-active");
        activeBtn->addStyleClass("nav-btn");
    }

    activeBtn = btn;
    
    if (activeBtn != nullptr) {
        activeBtn->removeStyleClass("nav-btn");
        activeBtn->addStyleClass("nav-btn-active");
    }
}

projectNavView::projectNavView(Project project,
    std::vector<RiskItem> risks,
    std::shared_ptr<RiskManager> riskManager)
    : Wt::WContainerWidget(),
    project_(project),
    risks_(risks),
    riskManager_(riskManager)
{
    contentArea_ = nullptr;
    activeBtn = nullptr;

    this->addStyleClass("project-nav-view");
    buildNavProj();
}


void projectNavView::buildNavProj()
{
    auto titleBar = addWidget(make_unique<Wt::WContainerWidget>());
    titleBar->addStyleClass("header-title-bar");
    
    //titleBar->addWidget(make_unique<Wt::WText>("Software Risk Tracker"));
    
    //auto logoutBtn = titleBar->addWidget(make_unique<Wt::WPushButton>("Logout"));
    //logoutBtn->addStyleClass("logout-btn");

    auto navRow = addWidget(make_unique<Wt::WContainerWidget>());
    navRow->addStyleClass("nav-links-row");

    backBtn = navRow->addWidget(make_unique<Wt::WPushButton>("Close"));
    backBtn->addStyleClass("nav-btn-back");

    //viewBtn = navRow->addWidget(make_unique<Wt::WPushButton>("Project view"));
    //viewBtn->addStyleClass("nav-btn");
    
    riskBtn = navRow->addWidget(make_unique<Wt::WPushButton>("Risks"));
    riskBtn->addStyleClass("nav-btn");


    matrixBtn = navRow->addWidget(make_unique<Wt::WPushButton>("Display Matrix"));
    matrixBtn->addStyleClass("nav-btn");

    exportBtn = navRow->addWidget(make_unique<Wt::WPushButton>("Export CSV"));
    exportBtn->addStyleClass("nav-btn");

    contentArea_ = addWidget(make_unique<Wt::WContainerWidget>());
    contentArea_->addStyleClass("content-display");

    riskBtn->clicked().connect([this]() {
        setActive(riskBtn);
        contentArea_->clear();
        contentArea_->addWidget(
            std::make_unique<riskView>(
                project_.getID(),
                project_.getName(),
                riskManager_->listRisks(project_.getID()),
                riskManager_
            )
        );

    });

    
    matrixBtn->clicked().connect([this]() {
        setActive(matrixBtn);
        contentArea_->clear();
        // you have to initalize the risks before calling the riskMatrix app so when integratinging with DB remeber that please
        // thse are dummy risks for tseting and for a example
        contentArea_->addWidget(
            make_unique<RiskMatrixView>(
                riskManager_->listRisks(project_.getID())
            )
        );

        
    });
    exportBtn->clicked().connect([this]() {
    if (!riskManager_) {
        return;
    }

    auto risks = riskManager_->listRisks(project_.getID());

    exportResource_ = std::make_shared<RiskExportView>(risks);

    doJavaScript("window.location='" + exportResource_->url() + "';");
});

/*
    exportBtn->clicked().connect([this]() {
        vector<RiskItem> risks; 
        RiskItem r1; 
        r1.setRiskID(1); 
        r1.setRiskName("Data Breach"); 
        r1.setDesc("Sensitive data exposure"); 
        r1.setProbability(3); 
        r1.setImpact(3); 
        RiskItem r2; 
        r2.setRiskID(2); 
        r2.setRiskName("System Failure"); 
        r2.setDesc("Unexpected downtime"); 
        r2.setProbability(2); 
        r2.setImpact(4); 
        risks.push_back(r1); 
        risks.push_back(r2);

        exportResource_ = std::make_shared<RiskExportView>(risks);

        doJavaScript("window.location='" + exportResource_->url() + "';");
    });
*/

    
    contentArea_->clear();
    contentArea_->addWidget(
        make_unique<RiskMatrixView>(
            riskManager_->listRisks(project_.getID())
        )
    );
    
    //contentArea_->clear();
    //contentArea_->addWidget(
        //make_unique<RiskMatrixView>(
            //riskManager_->listRisks(project_.getID())
        //)
    //);
    
    setActive(matrixBtn);
}

