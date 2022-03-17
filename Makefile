CC = gcc
WINCC = x86_64-w64-mingw32-gcc
SRC = modules/qtimp.c modules/image.c modules/utilities.c modules/quadtree.c modules/functions.c modules/cmdline.c
INC = include
BUILD = build
EXEC = qtimp
CFLAGS = -s -static -Werror -Wall -Wextra -Wshadow -Wunused-parameter -pedantic -I
LIBS = -lm
CDIR = mkdir -p

all: clean linux mingw-win

linux:
	$(CDIR) $(BUILD) && $(CC) $(CFLAGS) $(INC) $(SRC) -o $(BUILD)/$(EXEC)-linux-x86_64 $(LIBS)

mingw-win:
	$(CDIR) $(BUILD) && $(WINCC) $(CFLAGS) $(INC) $(SRC) -o $(BUILD)/$(EXEC)-windows-x86_64.exe -Os

windows:
	$(WINCC) $(CFLAGS) $(INC) $(SRC) -o $(EXEC)-windows-x86_64.exe -Os

clean:
	rm -rf $(BUILD)
