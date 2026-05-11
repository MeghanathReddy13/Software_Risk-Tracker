/* * Witty Text Box model implementation 
 * 2/1/2026, Hannah Lanier 
 */

#include "wittyTest.h"

namespace witty {
WittyTest::WittyTest() : status_("") {
}

void WittyTest::processClick() {
    status_ = "it works";
}

/**
 * Returns the current state. Marked const to match the header 
 */
std::string WittyTest::getStatus() const {
    return status_;
}

} // namespace witty
