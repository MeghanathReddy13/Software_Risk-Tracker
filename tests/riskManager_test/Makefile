ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model
TEST_FOLDER=${ROOT}/tests/riskManager_test

SRCS= driver.cpp riskManagerTest.cpp riskManagerModel.cpp databaseModel.cpp databaseManagerModel.cpp riskItemModel.cpp projectModel.cpp

OBJS=${SRCS:S/cpp$/o/g}

.PATH: ${MODEL_FOLDER} ${TEST_FOLDER}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lwtdbo -lwtdbosqlite3 -lwt

.PHONY: all clean test

all: riskManagerTest

riskManagerTest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

test: riskManagerTest
	@./riskManagerTest 2>/dev/null || ./riskManagerTest

clean: 
	@rm -f riskManagerTest *.o *.core *.db
