ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model
TEST_FOLDER=${ROOT}/tests/login_test

SRCS= driver.cpp loginTest.cpp loginModel.cpp userManagerModel.cpp authManagerModel.cpp databaseManagerModel.cpp databaseModel.cpp

OBJS=${SRCS:S/cpp$/o/g}

.PATH: ${MODEL_FOLDER} ${TEST_FOLDER}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lwtdbo -lwtdbosqlite3 -lwt -lcrypto

.PHONY: all clean

all: loginTest

loginTest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

test: loginTest
	@./loginTest 2>/dev/null || ./loginTest

clean: 
	@rm -f loginTest *.o *.core *.db
