#!/usr/bin/make

CC=g++ --std=c++11
CFLAGS=-Werror -Wall

LIBDIR=lib
SRCDIR=src

.PHONY: all clean

all: run generate

run: $(LIBDIR)/libprocess.so main.cpp
	$(CC) $(CFLAGS) -I$(SRCDIR) -L$(LIBDIR) -lprocess main.cpp -o $@

generate: $(LIBDIR)/libprocess.so generate.cpp
	$(CC) $(CFLAGS) -I$(SRCDIR) -L$(LIBDIR) -lprocess generate.cpp -o $@

$(LIBDIR)/libprocess.so: $(SRCDIR)/process.cpp
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@

# phony rules

clean:
	@rm -f $(LIBDIR)/*.so
	@rm -f run generate

