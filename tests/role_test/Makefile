ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model
TEST_FOLDER=${ROOT}/tests/role_test

SRCS= driver.cpp roleModelTest.cpp databaseModel.cpp databaseManagerModel.cpp userModel.cpp roleModel.cpp

OBJS=${SRCS:S/cpp$/o/g}

.PATH: ${MODEL_FOLDER} ${TEST_FOLDER}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lwtdbo -lwtdbosqlite3 -lwt

.PHONY: all clean test

all: roleTest

roleTest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

test: roleTest
	@./roleModelTest 2>/dev/null || ./roleTest

clean: 
	@rm -f roleTest *.o *.db *.core
