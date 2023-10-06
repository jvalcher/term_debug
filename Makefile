
# make				- build production binary
# make dev			- build development binary, run it
# make colors		- check if current terminal can display colors

CC=			gcc
FLAGS=		-Wall -MMD
PROD_FLAGS=	-O3
DEV_FLAGS=	-g -DRENDER_PRINT 

B_FILE_DEV=		termide-dev
B_FILE_PROD=	termide

C_FILES=	$(wildcard ./src/*.c)
O_FILES=	$(patsubst ./src/%.c, ./obj/%.o, $(C_FILES))
D_FILES= 	$(patsubst ./src/%.c, ./obj/%.d, $(C_FILES))

.PHONY: all dev colors


# build

all: FLAGS += $(PROD_FLAGS)
all: clean $(B_FILE_PROD)

dev: FLAGS += $(DEV_FLAGS)
dev: $(B_FILE_DEV)
	./$(B_FILE_DEV)

$(B_FILE_PROD): $(O_FILES)
	$(CC) -o $@ $^ -lncurses

$(B_FILE_DEV): $(O_FILES)
	$(CC) -o $@ $^ -lncurses

obj/%.o: src/%.c
	$(CC) $(FLAGS) -c -o $@ $<

-include $(D_FILES)

clean:
	rm -f ./obj/*
	rm -f ./gdb-tuiffic
	rm -f ./gdb-tuiffic-dev


# misc

colors:
	@./scripts/run ./scripts/colors_test.c
	@rm ./scripts/colors_test
