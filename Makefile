CC=gcc
BIN=tmd

all: $(BIN)

$(BIN): %: %.c
	$(CC) -o $@ $< -lmd4c

clean:
	rm $(BIN)

install:
	cp tmd /usr/bin/tmd
#	cp tmd.1 /usr/share/man/man1/

strip:
	strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag tmd
