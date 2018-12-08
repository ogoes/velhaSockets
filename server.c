#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "velha.h"


char *path = "\0hidden";

void cathPos(int * i, int * j, int pos) {

	if (pos <= 3 && pos > 0) {
		*i = 0;
		*j = pos-1;
	} else if (pos > 3 && pos <= 6) {
		*i = 1;
		*j = pos-4;

	} else if (pos > 6 && pos <= 9) {
		*i = 2;
		*j = pos - 7;
	}
}

int createSocket() {
	struct sockaddr_un addr;
	int sock;


	if ( (sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("ERRO!");
		exit(0);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;


	*addr.sun_path = '\0';
	strncpy(addr.sun_path+1, path+1, sizeof(addr.sun_path)-2);

	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
	    perror("ERRO no bind");
	    exit(0);
	}
  	if (listen(sock, 20) == -1) {
	    perror("Erro no listen");
	    exit(0);
	}
	return sock;
}

void enviaMatriz(int sockett) {

	char ** a = desenha_velha();
	
    for (int x = 0; x < 7; ++x) {
    	send(sockett, a[x], 16, 0);
    	recv(sockett, a[x], 16, 0);
        // printf("%s", a[x]), free(a[x]);
    }
}


int main(int argc, char *argv[]) {
	char buffer[200];
	char simbols[] = {'X', 'O', '\0'};

	int newSocket;
	
	int sock = createSocket(path);	

	int conexao = 0;
	while (1) {
		int player1 = accept(sock, NULL, NULL);
		int player2 = accept(sock, NULL, NULL);
		if ( player1 == -1 || player2 == -1 ) {
			perror("Erro na aceitaçao");
			continue;
	    } else {
		    if (fork() == 0) { // processo filho
		    	int i, j;
		    	int vez = 0;
		    	int playersSocks[] = {player1, player2};


		    	int player = 0;
	    		// send(playersSocks[vez], "Go", 3, 0);

		    	inicio_velha();
		    	char ** a = desenha_velha();
	
			    for (int x = 0; x < 7; ++x) {
			    	printf("%s", a[x]);
      
			    }
		    	

		    	while (1) {
		    	
		    		int pos;
		    		do {

			    		send(playersSocks[vez], "Go", 3, 0);
						recv(playersSocks[vez], buffer, 2, 0);

		    			buffer[1] = '\0';
		    			pos = atoi(buffer);
		    			i = j = 10;
		    		} while (pos < 1 || pos > 9);

	    			cathPos(&i, &j, pos);

					marca_velha(i, j, simbols[vez]);

		    		char resp = verifica_ganhador();
					if (resp != ' ') { 
						if (resp == 0) printf ("\n\nEmpate!!!!!!!\n\n", resp);
						else {
							printf ("\n\nGanhador eh %c\n\n", resp);
							send(playersSocks[vez], "Win", 4, 0);
						}
						// exit(1);
						break;
					} //if

					vez = (vez + 1) % 2;

					a = desenha_velha();
	
				    for (int x = 0; x < 7; ++x) {
				    	printf("%s", a[x]);
				    }

					recv(playersSocks[vez], buffer, 2, 0);	

		    	}
	    		printf("Conexão %i Terminada\n", conexao);
	    		close(playersSocks[0]);
	    		close(playersSocks[1]);
		    	
	    		exit(0);
		    }
		    conexao += 1;
	    }
	}
}