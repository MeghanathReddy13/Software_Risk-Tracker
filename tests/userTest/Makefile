# Shelby Stanly
ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model

SRCS= driver.cpp userTest.cpp \
	userModel.cpp userManagerModel.cpp databaseManagerModel.cpp databaseModel.cpp \
	authManagerModel.cpp
OBJS=${SRCS:S/cpp$/o/g}

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}
LDFLAGS=-L/usr/local/lib -lgtest -lgtest_main -lwtdbo -lwtdbosqlite3 -lwt -lssl -lcrypto

.PHONY: all clean

.PATH:=${MODEL_FOLDER}

all: userTest

userTest: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

userModel.o: ${MODEL_FOLDER}/userModel.cpp ${MODEL_FOLDER}/userModel.h
userManagerModel.o: ${MODEL_FOLDER}/userManagerModel.cpp ${MODEL_FOLDER}/userManagerModel.h
databaseModel.o: ${MODEL_FOLDER}/databaseModel.cpp ${MODEL_FOLDER}/databaseModel.h
databaseManagerModel.o: ${MODEL_FOLDER}/databaseManagerModel.cpp ${MODEL_FOLDER}/databaseManagerModel.h
authManagerModel.o: ${MODEL_FOLDER}/authManagerModel.cpp ${MODEL_FOLDER}/authManagerModel.h
#riskSchemaModel.o: ${MODEL_FOLDER}/riskSchemaModel.h 

test: userTest
	@./userTest 2>/dev/null || ./userTest

clean:
	@rm -f userTest *.o *.core *.db
