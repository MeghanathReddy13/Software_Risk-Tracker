#include "riskMatrixView.h"
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <Wt/WTableCell.h>
#include <Wt/WApplication.h>
#include <vector>
#include <string>

using namespace std;
using namespace Wt;

RiskMatrixView::RiskMatrixView(const vector<RiskItem>& risks)
    : WContainerWidget()
{
    
    WApplication::instance()->useStyleSheet("riskMatrixView.css");
    this->addStyleClass("matrix-container");
    
    buildMatrix(risks);
}

void RiskMatrixView::buildMatrix(const vector<RiskItem>& risks)
{

    //LEGEND
    // Creates a key to explain the colors
    auto legendInfo = addWidget(make_unique<WContainerWidget>());
    legendInfo->addStyleClass("matrix-legend");
    legendInfo->addWidget(make_unique<WText>("Risk Level: "));

    // Helper to nke  said entry
    auto addLegendItem = [&](string label, string colorClass) {
        auto item = legendInfo->addWidget(make_unique<WContainerWidget>());
        item->addStyleClass("legend-item");
        item->addWidget(make_unique<WContainerWidget>())->addStyleClass("legend-box " + colorClass);
        item->addWidget(make_unique<WText>(label));
    };

    addLegendItem("Low", "risk-low");
    addLegendItem("Medium", "risk-medium");
    addLegendItem("High", "risk-high");
    addLegendItem("Critical", "risk-critical");

    // TABLE 
    matrixTable_ = addWidget(make_unique<WTable>());
    matrixTable_->addStyleClass("risk-matrix-table");

    // sets the label on the top left
    auto cornerCell = matrixTable_->elementAt(0, 0);
    cornerCell->addWidget(make_unique<WText>("<b>Likelihood</b><br/><small>Impact →</small>"));

    // labels 
    vector<string> impacts = {"Negligible (1)", "Minor (2)", "Moderate (3)", "Major (4)", "Severe (5)"};
    vector<string> likelihoods = {"Rare (1)", "Unlikely (2)", "Possible (3)", "Likely (4)", "Almost Certain (5)"};


    // populate the Impactrs and likelihoods
    for (int i = 0; i < 5; ++i) {
        matrixTable_->elementAt(0, i + 1)->addWidget(make_unique<WText>(impacts[i]));

        matrixTable_->elementAt(5 - i, 0)->addWidget(make_unique<WText>(likelihoods[i]));
    }


    // GRID
    for (int l = 5; l >= 1; --l) {
        for (int i = 1; i <= 5; ++i) { 
            int tableRow = 6 - l;
            int score = l * i;
            
            WTableCell* cell = matrixTable_->elementAt(tableRow, i);
            cell->addStyleClass("matrix-cell " + getColorClass(score));
            
        
            auto scoreLabel = cell->addWidget(make_unique<WText>(to_string(score)));
            scoreLabel->addStyleClass("cell-score");


            bool riskFound = false;
            auto card = make_unique<WContainerWidget>();
            card->addStyleClass("risk-card");
            

            // look through every risk 
            for (const auto& r : risks) {
                //if this matches the card we currenty ar on it adds it to it
                if (r.getProbability() == l && r.getImpact() == i) {
                    card->addWidget(make_unique<WText>("<br/>" + r.getRiskName()));
                    riskFound = true;
                }
            }

            // if we found atlest  single one its added else it adds the text
            if (riskFound) {
                cell->addWidget(std::move(card));
            } else {
                cell->addWidget(make_unique<WText>("No risks"))->addStyleClass("no-risks-text");
            }
        }
    }
}

string RiskMatrixView::getColorClass(int score) {
    if (score >= 20) return "risk-critical";
    if (score >= 12) return "risk-high";
    if (score >= 6) return "risk-medium";
    return "risk-low";
}