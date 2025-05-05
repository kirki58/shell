CC = gcc
INCLUDE = -I include
OPT = -O0
CFLAGS = -Wall -Wextra -g $(INCLUDE) $(OPT)

CFILES := $(shell find src/ -type f -name "*.c")
OBJFILES := $(patsubst src/%.c,obj/%.o,$(CFILES)) # Corresponding .o files of the CFILES

TESTFILES := $(shell find test/ -type f -name "*.c")
TESTOBJFILES := $(patsubst test/%.c, test/obj/%.o,$(TESTFILES)) # Corresponding .o files of the TESTFILES
OBJEXCL := $(filter-out obj/main.o, $(OBJFILES))

BIN = bin/shell
TESTBIN = bin/shell_tests

all: $(BIN)

$(BIN): $(OBJFILES)
	mkdir -p bin
	$(CC) -o $@ $^

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $^

# Run tests
run: $(TESTBIN)
	./$(TESTBIN)

# Build tests
test: $(TESTBIN)

$(TESTBIN): $(OBJEXCL) $(TESTOBJFILES) test/lib/unity.o
	mkdir -p bin
	$(CC) -o $@ $^

test/obj/%.o: test/%.c
	mkdir -p test/obj
	$(CC) $(CFLAGS) -I third_party -c -o $@ $^

test/lib/unity.o: third_party/unity.c
	mkdir -p test/lib
	gcc -I include -I third_party -O2 -c -o test/lib/unity.o third_party/unity.c

# Clean the build
clean:
	rm -rf bin
	rm -rf obj
	rm -rf test/obj

.PHONY: all clean run test