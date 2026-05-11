#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

#include <memory>
#include <string>
#include <vector>

#include "../model/riskItemModel.h"
#include "../model/riskManagerModel.h"

class riskView : public Wt::WContainerWidget {
    public: 
        riskView(int projectID,
            const std::string &projectName,
            std::vector<RiskItem> risks,
            std::shared_ptr<RiskManager> riskManager
        );

    private:
        void buildView();
        void refreshRiskList();

        void addRiskCard(int riskID,
            const std::string& name,
            const std::string& desc,
            int prob,
            int impact);

        int projectID;        
        std::string projectName_;
        std::vector<RiskItem> risks_;
        std::shared_ptr<RiskManager> riskManager_;

        Wt::WContainerWidget* riskList_;
        Wt::WText* statusText_;
};

