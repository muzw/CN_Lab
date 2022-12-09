all: build/rdt_stopwait_receiver build/rdt_stopwait_sender

build/%: %.c net.c net.h | build
	gcc -Wall -o $@ $< net.c

build:
	mkdir -p build

clean:
	rm -r build

sender:net.c net.h rdt_stopwait_sender.c
	gcc net.c net.h rdt_stopwait_sender.c -o sender

.PHONY: all clean
