EXE?=saper
TARGET=$(BUILDDIR)/$(EXE)

SRCDIR=src
BUILDDIR=_build
$(shell mkdir -p $(BUILDDIR))

SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

NCURSES_LIB?=ncurses
NCURSES_CFLAGS?=`pkg-config --cflags $(NCURSES_LIB)`
NCURSES_LDLIBS?=`pkg-config --libs $(NCURSES_LIB)`

CC=gcc
CFLAGS?=-Wall -Wextra -Wshadow -pedantic -std=c11 -O2 $(NCURSES_CFLAGS)
LDLIBS?=$(NCURSES_LDLIBS)

PREFIX?=/usr/local
BINDIR?=$(PREFIX)/bin


.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDLIBS)

%.o : %.c

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@-rm -r $(BUILDDIR)

install: $(TARGET)
	install -m 755 $(TARGET) $(BINDIR)

uninstall:
	rm $(BINDIR)/$(EXE)