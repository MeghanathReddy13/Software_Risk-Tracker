#include "riskExportView.h"

RiskExportView::RiskExportView(const std::vector<RiskItem>& risks)
    : risks_(risks) {}

void RiskExportView::handleRequest(const Wt::Http::Request&,
                                   Wt::Http::Response& response)
{
    // Set response headers for CSV download
    response.setMimeType("text/csv");
    response.addHeader("Content-Disposition", "attachment; filename=risks.csv");

    std::ostream& out = response.out();

    // Optional: UTF-8 BOM (helps Excel open correctly)
    out << "\xEF\xBB\xBF";

    // CSV header row
    out << "ID,Name,Description,Likelihood,Impact\n";

    // Data rows
    for (const auto& r : risks_) {
        out << r.getRiskID() << ","
            << escape(r.getRiskName()) << ","
            << escape(r.getDesc()) << ","
            << r.getProbability() << ","
            << r.getImpact() << "\n";
    }
}

// Escapes commas, quotes, and newlines
std::string RiskExportView::escape(const std::string& field) const
{
    if (field.find(',') != std::string::npos ||
        field.find('"') != std::string::npos ||
        field.find('\n') != std::string::npos)
    {
        std::string result = "\"";
        for (char c : field) {
            if (c == '"') {
                result += "\"\""; // escape quotes
            } else {
                result += c;
            }
        }
        result += "\"";
        return result;
    }

    return field;
}
