/* Brandon Zuniga */
/* 2/20/2026 */

#ifndef RISKEXPORTVIEW_H
#define RISKEXPORTVIEW_H

#include <Wt/WResource.h>
#include <Wt/Http/Response.h>
#include <vector>
#include <string>
#include "../model/riskItemModel.h"

class RiskExportView : public Wt::WResource {
public:
    // Constructor
    RiskExportView(const std::vector<RiskItem>& risks);

    // Handles the download request
    void handleRequest(const Wt::Http::Request& request,
                       Wt::Http::Response& response) override;

private:
    std::vector<RiskItem> risks_;

    // Helper to escape CSV fields
    std::string escape(const std::string& field) const;
};

#endif // RISKEXPORTVIEW_H
