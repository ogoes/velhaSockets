all: server client

server:
	gcc server.c velha.c -o server
client:
	gcc client.c -o client
clean:
	rm -rf client server; make
