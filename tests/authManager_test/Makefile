ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model
TEST_FOLDER=${ROOT}/tests/authManager_test

SRCS= driver.cpp authManagerTest.cpp databaseModel.cpp databaseManagerModel.cpp userModel.cpp authManagerModel.cpp

OBJS=${SRCS:S/cpp$/o/g}

.PATH: ${MODEL_FOLDER} ${TEST_FOLDER}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lwtdbo -lwtdbosqlite3 -lwt -lcrypto

.PHONY: all clean test

all: authTest

authTest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

test: authTest
	@./authTest 2>/dev/null || ./authTest

clean: 
	@rm -f authTest *.o *.db *.core

