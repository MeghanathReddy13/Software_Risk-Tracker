ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model
TEST_FOLDER=${ROOT}/tests/riskItem_test

SRCS= driver.cpp riskItemTest.cpp databaseModel.cpp databaseManagerModel.cpp riskItemModel.cpp userModel.cpp

OBJS=${SRCS:S/cpp$/o/g}

.PATH: ${MODEL_FOLDER} ${TEST_FOLDER}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lwtdbo -lwtdbosqlite3 -lwt

.PHONY: all clean test

all: riskItemTest

riskItemTest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

test: riskItemTest
	@./riskItemTest 2>/dev/null || ./riskItemTest

clean: 
	@rm -f riskItemTest *.o *.db *.core
