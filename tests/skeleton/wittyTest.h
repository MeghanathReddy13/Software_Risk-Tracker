/* * Witty Text Box model header 
 * 2/1/2026, Hannah Lanier 
 */

#ifndef WITTY_TEST_H
#define WITTY_TEST_H

#include <string>

namespace witty {

class WittyTest {
public:
    WittyTest();

    /**
     * @brief Updates the internal state to "it works"
     */
    void processClick();

    /**
     * @brief Gets the current status message
     * @return std::string The current status
     */
    std::string getStatus() const;

private:
    std::string status_;
};

} // namespace witty

#endif // WITTY_TEST_H
