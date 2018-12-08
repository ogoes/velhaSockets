/*
 * Especifica as vari�veis e fun��es para o jogo da velha
 **/

char velha[3][3];
int contador;

void inicio_velha();                           /* inicializa as vari�veis do jogo */
char ** desenha_velha();                          /* desenha o tabuleiro e as posi��es preenchidas */
char verifica_ganhador();                      /* verifica se h� ganhador ou empate, retorna sinal ganhador */ 
int marca_velha (int l, int c, char sinal);    /* seta uma posi��o com um determinado sinal 
                                                 (retorna 1 sucesso e -1 posi��o inv�lida */

