FILES = source/main.cpp source/app.cpp source/directory.cpp
CFLAGS = -Wall -Wextra -std=c++17 -pedantic -ggdb -O1
LINKS = -lncurses -lmenu
all:
	g++ ${FILES} ${CFLAGS} -o project_creation ${LINKS}
