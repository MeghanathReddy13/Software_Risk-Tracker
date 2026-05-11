# Shelby Stanly
ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model

SRCS= driver.cpp dbTest.cpp \
	databaseModel.cpp
OBJS=${SRCS:S/cpp$/o/g}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}
LDFLAGS=-L/usr/local/lib -lgtest -lgtest_main -lwtdbo -lwtdbosqlite3 -lwt

.PHONY: all clean

.PATH:=${MODEL_FOLDER}

all: dbTest

dbTest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

databaseModel.o: ${MODEL_FOLDER}/databaseModel.cpp ${MODEL_FOLDER}/databaseModel.h
riskSchemaModel.o: ${MODEL_FOLDER}/riskSchemaModel.h 

test: dbTest
	@./dbTest 2>/dev/null || ./dbTest

clean:
	@rm -f dbTest *.o *.core *.db
