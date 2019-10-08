# Begin Makefile

CC = clang

CPPFLAGS = -Iinclude
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

SRC = \
	  src/main.c

OBJ = $(SRC:.c=.o)

all: release

boi: $(OBJ)
boi:
	$(CC) $^ -o $@

release: CFLAGS += -Os
release: boi

debug: CPPFLAGS += -D_BOI_DEBUG
debug: CFLAGS += -O0 -g3
debug: boi

clean:
	$(RM) $(OBJ)
	$(RM) boi

.PHONY: all clean release debug

# End Makefile
