# Alli - 03/17/2026

ROOT!= git rev-parse --show-toplevel
MODEL_FOLDER=${ROOT}/src/model

SRCS= main.cpp dbmTest.cpp \
      ${MODEL_FOLDER}/databaseManagerModel.cpp \
      ${MODEL_FOLDER}/userModel.cpp \
      ${MODEL_FOLDER}/projectModel.cpp \
      ${MODEL_FOLDER}/riskItemModel.cpp \
      ${MODEL_FOLDER}/databaseModel.cpp

CXXFLAGS=-Wall -std=c++20
CXXFLAGS+=-I/usr/local/include -I${MODEL_FOLDER}

LDFLAGS=-L/usr/local/lib -lgtest -lgtest_main -lwt -lwtdbo -lwtdbosqlite3 -lpthread

.PHONY: all clean test

all: dbmTestUser

# ✅ Compile EVERYTHING together (simplest working solution)
dbmTestUser:
	${CXX} ${CXXFLAGS} -o $@ ${SRCS} ${LDFLAGS}

test: dbmTestUser
	./dbmTestUser

clean:
	rm -f dbmTestUser *.o *.core *.db
