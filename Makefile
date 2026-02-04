CXX := clang++
AR := ar

CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic -Iinclude
PREFIX ?= /usr/local

SRC := src/m4a_to_wav.cpp
OBJ := build/m4a_to_wav.o
LIB := lib/libm4amortal.a
CLI := bin/m4amortal

.PHONY: all clean install

all: $(LIB) $(CLI)

build:
	mkdir -p build

lib:
	mkdir -p lib

bin:
	mkdir -p bin

$(OBJ): $(SRC) include/m4a_to_wav.h | build
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

$(LIB): $(OBJ) | lib
	$(AR) rcs $(LIB) $(OBJ)

$(CLI): examples/main.cpp $(LIB) | bin
	$(CXX) $(CXXFLAGS) examples/main.cpp $(LIB) -o $(CLI)

install: all
	mkdir -p "$(DESTDIR)$(PREFIX)/bin" "$(DESTDIR)$(PREFIX)/include" "$(DESTDIR)$(PREFIX)/lib"
	install -m 755 "$(CLI)" "$(DESTDIR)$(PREFIX)/bin/m4amortal"
	install -m 644 include/m4a_to_wav.h "$(DESTDIR)$(PREFIX)/include/m4a_to_wav.h"
	install -m 644 "$(LIB)" "$(DESTDIR)$(PREFIX)/lib/libm4amortal.a"

clean:
	rm -rf build lib bin
