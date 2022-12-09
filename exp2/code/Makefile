all: build/ts build/tc build/us build/uc build/my_ts build/my_tc build/my_us build/my_uc

build/ts: tcp_server.c net.h | build
	gcc -o build/ts tcp_server.c

build/tc: tcp_client.c net.h | build
	gcc -o build/tc tcp_client.c

build/us: udp_server.c net.h | build
	gcc -o build/us udp_server.c

build/uc: udp_client.c net.h | build
	gcc -o build/uc udp_client.c


#my
build/my_ts: my_tcp_server.c net.h | build
	gcc -o build/my_ts my_tcp_server.c

build/my_tc: my_tcp_client.c net.h | build
	gcc -o build/my_tc my_tcp_client.c

build/my_us: my_udp_server.c net.h | build
	gcc -o build/my_us my_udp_server.c

build/my_uc: my_udp_client.c net.h | build
	gcc -o build/my_uc my_udp_client.c

build:
	mkdir -p build

clean:
	rm -r build

.PHONY: all clean
