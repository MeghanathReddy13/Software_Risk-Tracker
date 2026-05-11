#include "riskAddForm.h"
#include "riskEditForm.h"
#include "riskView.h"
#include "riskItemModel.h"
#include "confirmDialog.h"

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include <memory>
#include <string>
#include <vector>

riskView::riskView(int projectID,
    const std::string& projectName,
    std::vector<RiskItem> risks,
    std::shared_ptr<RiskManager> riskManager)
    : Wt::WContainerWidget(),
      projectID(projectID),
      projectName_(projectName),
      risks_(risks),
      riskManager_(riskManager)
{
    this->addStyleClass("content-display");
    buildView();
}

void riskView::buildView()
{
    auto title = addWidget(std::make_unique<Wt::WText>(
        "Risks in Project: " + projectName_));
    title->addStyleClass("project-title-header");

    statusText_ = addWidget(std::make_unique<Wt::WText>(""));
    statusText_->addStyleClass("project-list-subtitle");

    auto addRiskBtn = addWidget(std::make_unique<Wt::WPushButton>("Add Risk"));
    addRiskBtn->addStyleClass("save-edit-btn");
    addRiskBtn->clicked().connect([this]() {
        clear();
        addWidget(std::make_unique<RiskAddForm>(riskManager_,
            projectID,
            [this]() {
                risks_ = riskManager_->listRisks(projectID);
                clear();
                buildView();
            }));
    });

    riskList_ = addWidget(std::make_unique<Wt::WContainerWidget>());
    riskList_->addStyleClass("risk-list-wrapper");

    refreshRiskList();
}

void riskView::refreshRiskList()
{
    riskList_->clear();

    if (risks_.empty()) {
        statusText_->setText("No risks found for this project.");
        return;
    }

    statusText_->setText(std::to_string(risks_.size()) + " risks found for this project.");

    for (const auto &risk : risks_) {
        addRiskCard(
            risk.getRiskID(),
            risk.getRiskName(),
            risk.getDesc(),
            risk.getProbability(),
            risk.getImpact()
        );
    }
}

void riskView::addRiskCard(int riskID,
    const std::string& name,
    const std::string& desc,
    int prob,
    int impact)
{
    auto card = riskList_->addWidget(std::make_unique<Wt::WContainerWidget>());
    card->addStyleClass("project-row");

    auto info = card->addWidget(std::make_unique<Wt::WContainerWidget>());
    info->addStyleClass("project-info");

    info->addWidget(std::make_unique<Wt::WText>(name))->addStyleClass("project-name");

    info->addWidget(std::make_unique<Wt::WBreak>());

    info->addWidget(std::make_unique<Wt::WText>(desc))->addStyleClass("project-meta");

    auto scoreBox = card->addWidget(std::make_unique<Wt::WContainerWidget>());
    scoreBox->addStyleClass("risk-score-box");

    scoreBox->addWidget(std::make_unique<Wt::WText>("Likelihood: " + std::to_string(prob)));
    scoreBox->addWidget(std::make_unique<Wt::WBreak>());

    scoreBox->addWidget(std::make_unique<Wt::WText>("Impact: " + std::to_string(impact)));
    scoreBox->addWidget(std::make_unique<Wt::WBreak>());

    scoreBox->addWidget(std::make_unique<Wt::WText>("Score: " + std::to_string(prob * impact)));

    scoreBox->addWidget(std::make_unique<Wt::WBreak>());

    auto editBtn = scoreBox->addWidget(std::make_unique<Wt::WPushButton>("Edit Risk"));
    editBtn->addStyleClass("save-edit-btn");

    editBtn->clicked().connect([this, riskID, name, desc, prob, impact]() {
        clear();
        addWidget(std::make_unique<RiskEditForm>(
            riskManager_,
            riskID,
            name,
            desc,
            prob,
            impact,
            [this]() {
                risks_ = riskManager_->listRisks(projectID);
                clear();
                buildView();
            }
        ));
    });


    auto deleteBtn = scoreBox->addWidget(std::make_unique<Wt::WPushButton>("Delete Risk"));
    deleteBtn->addStyleClass("delete-btn");

    deleteBtn->clicked().connect([this, riskID, name]() {
        if(!riskManager_) {
            return;
        }
	Wt::WApplication::instance()->root()->addWidget(
		std::make_unique<ConfirmDialog>(
			"Delete Risk",
			"Are You sure you want to delete\""+name +"\"?",
			[this,riskID](){
			if(!riskManager_) return;

		        riskManager_->deleteRisk(riskID);
        		risks_ = riskManager_->listRisks(projectID);
        		refreshRiskList();
			}
	)
    );
});
}
