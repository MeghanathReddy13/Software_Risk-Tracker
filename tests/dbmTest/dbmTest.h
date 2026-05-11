// Alli */
/* 03/17/2026 */

#ifndef DBMTEST_H
#define DBMTEST_H

#include <gtest/gtest.h>
#include "../../src/model/databaseManagerModel.h"
#include "../../src/model/userModel.h"
#include "../../src/model/projectModel.h"
#include "../../src/model/riskItemModel.h"

class DatabaseManager;

class DatabaseManagerTest : public ::testing::Test {
protected:
    DatabaseManagerTest()
        : dbm() {}

    void SetUp() override {
        //Before each test
    }

    void TearDown() override {
        //After each test, optional (?)
    }

    DatabaseManager dbm;
};

#endif // DBMTEST_H
