ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model
TEST_FOLDER=${ROOT}/tests/projectManager_test

SRCS= driver.cpp projectManagerTest.cpp databaseModel.cpp databaseManagerModel.cpp projectModel.cpp userModel.cpp projectManagerModel.cpp

OBJS=${SRCS:S/cpp$/o/g}

.PATH: ${MODEL_FOLDER} ${TEST_FOLDER}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lwtdbo -lwtdbosqlite3 -lwt

.PHONY: all clean test

all: projectManagerTest

projectManagerTest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

test: projectManagerTest
	@./projectManagerTest 2>/dev/null || ./projectManagerTest

clean: 
	@rm -f projectManagerTest *.o *.db *.core
