#ifndef WITTY_TEST_H
#define WITTY_TEST_H

#include <string>

namespace witty {
    class WittyTest {
    public:
        WittyTest();
        void attemptLogin(const std::string& username, const std::string& password);
        std::string getStatus() const;
    private:
        std::string status_;
    };
}

#endif
