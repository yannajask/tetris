# Makefile, adapted from CS 246

CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Werror=vla -MD -fsanitize=undefined -D_DARWIN_C_SOURCE -DNCURSES_WIDECHAR -I/opt/homebrew/opt/ncurses/include -L/opt/homebrew/opt/ncurses/lib
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}

###

SOURCES = $(wildcard *.cc)
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = tetrisV2

###

.PHONY : clean

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@ -Wl,-search_paths_first,-search_dylibs_first -lncursesw

${OBJECTS}: ${MAKEFILE_NAME}

-include ${DEPENDS}

clean :
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
