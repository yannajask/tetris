### Makefile, adapted from CS 246

CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Werror=vla -MD -fsanitize=undefined -DNCURSES_WIDECHAR
LDFLAGS = -lncursesw

###

ifeq (${shell uname -s}, Darwin)
	CXXFLAGS += -D_DAWRIN_C_SOURCE -I/opt/homebrew/opt/ncurses/include
	LDFLAGS += -L/opt/homebrew/opt/ncurses/lib -Wl,-search_paths_first,-search_dylibs_first
endif

###

BUILD = build
EXEC = tetris

SOURCES = $(wildcard src/*.cc)
OBJECTS = ${patsubst src/%.cc, ${BUILD}/%.o, ${SOURCES}}
DEPENDS = ${OBJECTS:.o=.d}

###

.PHONY : clean setup

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o ${EXEC} ${LDFLAGS}

${BUILD}/%.o: src/%.cc | setup
	${CXX} ${CXXFLAGS} -c $< -o $@

setup:
	mkdir -p ${BUILD}

-include ${DEPENDS}

clean :
	rm -rf ${BUILD}/
