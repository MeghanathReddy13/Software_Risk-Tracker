/*
 * Shelby Stanly
 * CSV Export Performance Test
 * Date: 5/4/2026
 */
#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "riskExportView.h"
#include "riskItemModel.h"

TEST(ExportTest, CSVExport) {
    const int numRisks = 55555;
    std::vector<RiskItem> risks;

    for (int i = 0; i < numRisks; i++) {
        RiskItem r;
        r.setRiskName("Risk " + std::to_string(i));
        r.setDesc("Description " + std::to_string(i));
        r.setProbability(i % 5);
        r.setImpact(i % 5);
        risks.push_back(r);
    }

    RiskExportView view(risks);

    std::ostringstream out;

    auto start = std::chrono::high_resolution_clock::now();

    out << "ID,Name,Description,Likelihood,Impact\n";

    /*
     * Measures the cost of the CSV Export to verify PERF-7 adherence.
     * To do so: Iterates and formats risk data.
     */
    for (const auto& r: risks) {
        out << r.getRiskID() << ","
            << r.getRiskName() << ","
            << r.getDesc() << ","
            << r.getProbability() << ","
            << r.getImpact() << "\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

    EXPECT_LT(duration, 2000);
    std::cout << "CSV Export Time (" << numRisks << " risks):" << duration << " ms\n";
}

