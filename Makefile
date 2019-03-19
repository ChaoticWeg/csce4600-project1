#!/usr/bin/make

CC=g++ --std=c++11
CFLAGS=-Werror -Wall

NUM_PROCESSES=200

LIBDIR=lib
SRCDIR=src

.PHONY: all clean dirs ci data

all: dirs run generate

run: $(LIBDIR)/libprocess.so main.cpp
	$(CC) $(CFLAGS) -I$(SRCDIR) -L$(LIBDIR) -lprocess $(SRCDIR)/cpu.cpp main.cpp -o $@

generate: $(LIBDIR)/libprocess.so generate.cpp
	$(CC) $(CFLAGS) -I$(SRCDIR) -L$(LIBDIR) -lprocess generate.cpp -o $@

$(LIBDIR)/libprocess.so: $(SRCDIR)/process.cpp
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@

# phony rules

clean:
	@rm -f $(LIBDIR)/*.so
	@rm -f run generate

dirs:
	@mkdir -p lib
	@mkdir -p data

data: dirs generate
	@./generate $(NUM_PROCESSES) > data/processes.dat

ci: clean data run

