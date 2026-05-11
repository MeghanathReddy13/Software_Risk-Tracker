ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model
TEST_FOLDER=${ROOT}/tests/auditLog_test

SRCS= driver.cpp auditLogTest.cpp auditLogModel.cpp databaseModel.cpp databaseManagerModel.cpp

OBJS=${SRCS:S/cpp$/o/g}

.PATH: ${MODEL_FOLDER} ${TEST_FOLDER}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lwtdbo -lwtdbosqlite3 -lwt

.PHONY: all clean test

all: auditLogTest

auditLogTest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

test: auditLogTest
	@./auditLogTest 2>/dev/null || ./auditLogTest

clean: 
	@rm -f auditLogTest *.o *.core *.db
