#include <memory>
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>

#include "riskTrackerApp.h"

int 
main(int argc, char** argv) 
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<riskTrackerApp>(env);
    });
}
