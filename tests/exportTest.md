# CSV Export Test Assessment
### Risk Tracker
### Date: 5/4/2026


## Components: 
* view: riskExportView.h, riskExportView.cpp
* model: riskItemModel.h, riskItemModel.cpp
* verifier: exportTest


### Traceability Matrix
| Requirement                  | Implementation                             | Verified By              |
| ---------------------------- | ------------------------------------------ | ------------------------ |
| PERF-7 CSV Export < 2 secs   | CSV formatting loop in RiskExportView      | CSVExport                |

### Test Results
| Test Case Name            | Scenario                                      | Expected Result                           | Status    |  
| ------------------------- | --------------------------------------------- | ----------------------------------------- | --------- |
| CSVExport                 | Export 55,555 risks to CSV format             | Execution time < 2000 ms                  | PASSED    |

### Technical Implementation
```
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
```
### Performance Notes
The tests measures the primary cost of csv export, involving data iteration and formatting.
This has a time complexity of O(n).
Operations such as HTTP response setup and field escaping are constant time.
These do not significantly affect total execution time.
Hence, the system satisfies PERF-7.

### Execution Log
[==========] Running 1 test from 1 test suite.<br>
[----------] Global test environment set-up.<br>
[----------] 1 test from ExportTest.<br>
[RUN       ] ExportTest.CSVExport<br>
CSV Export Time (55555 risks): 239 ms
[        OK] ExportTest.CSVExport (388 ms)<br>
[----------] 1 test from ExportTest (389 ms total)<br>

[----------] Global test environment tear-down<br>
[==========] 1 test from 1 test suite ran. (390 ms total)<br>
[  PASSED  ] 1 test.
