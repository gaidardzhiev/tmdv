CC=gcc
BIN=tmdv

all: $(BIN)

$(BIN): %: %.c
	$(CC) -o $@ $< -lmd4c

clean:
	rm $(BIN)

install:
	cp tmdv /usr/bin/tmdv
#	cp tmdv.1 /usr/share/man/man1/

strip:
	strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag tmdv
