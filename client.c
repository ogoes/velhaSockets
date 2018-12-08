#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define WORD_LEN 100

char * path = "\0hidden";

int main () {
	struct sockaddr_un addr;
	char buffer[WORD_LEN];
	int sock;

	if ( (sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("ERRO!");
		exit(0);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;

	*addr.sun_path = '\0';
	strncpy(addr.sun_path+1, path+1, sizeof(addr.sun_path)-2);

	if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
	    perror("connect error");
	    exit(-1);
	}

	int condition = 1;
	int qtdeBytes = 0;
	while (condition) {
		buffer[0] = '\0';
		send(sock, "OK", 3, 0);
		recv(sock, buffer, sizeof(buffer), 0);
		printf("%s\n", buffer);
		if (strcmp(buffer, "Lose") == 0) {

		} else if (strcmp(buffer, "Win") == 0) {

		} else if (strcmp(buffer, "Go") == 0) {
			char pos[100];
			printf("Infome Uma posição: \n");
			scanf(" %s", pos);
			write(sock, pos, strlen(pos));
		} else {
	        printf("%s", buffer);
		}


		// printf("Digite o codigo e a palavra: ");
		// scanf(" %[^\n]s", buffer);
		// qtdeBytes = strlen(buffer);
		// if (qtdeBytes == 0) {
		// 	condition = 0;
		// 	break;
		// }
		// if (strcmp(buffer, "NO-NO") == 0) {
		// 	condition = 0;
		// 	break;
		// }
		// write(sock, buffer, qtdeBytes);
		// // send(sock, buffer, qtdeBytes, 0);
		
		// recv(sock, buffer, sizeof(buffer), 0);
		// printf("Tradução:  %s\n", buffer);
	}
}