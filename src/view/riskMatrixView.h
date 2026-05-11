#ifndef RISK_MATRIX_VIEW_H
#define RISK_MATRIX_VIEW_H

#include "riskItemModel.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <string>
#include <vector>

// not needed with riskItemModel
// struct Risk {
//     std::string name;
//     int likelihood; 
//     int impact;     
// };

class RiskMatrixView : public Wt::WContainerWidget {
public:
    RiskMatrixView(const std::vector<RiskItem>& risks);

private:
    void buildMatrix(const std::vector<RiskItem>& risks);
    std::string getColorClass(int score);
    Wt::WTable* matrixTable_;
};

#endif