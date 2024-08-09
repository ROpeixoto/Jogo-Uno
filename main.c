#include <stdio.h>
#include "pilha.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "UNO.h"
#include "types.h"
#include "listade.h"
#define resett "\033[0m"
#define vvermelho "\033[0;31m"
#define azzul "\033[0;34m"
#define amarello "\033[0;33m"
#define vverde "\033[0;38;2;0;255;0m"
#define roxxo "\033[0;35m"


int main(void) {



 char jogador1[21];
 char jogador2[21];
   FILE *uno;
  int c=0;
   uno = fopen("arquivo.txt", "w");
  printf("Insira o nome do jogador 1\n");
    scanf(" %s", jogador1);

   fprintf (uno, "Nome do Jogador 1 é %s\n",jogador1);

  printf("Insira o nome do jogador 2\n");
    scanf(" %s", jogador2);

    fprintf (uno, "Nome do jogador 2 é %s\n",jogador2);


    printf("\nBem vindos jogadores --> %s e %s\n\n\n", jogador1, jogador2);

    sleep(2);

    system("clear");

  tp_arvore vermelho,azul,amarelo,verde,especial;
  vermelho = inicializa_arvore();
  azul = inicializa_arvore();
  amarelo = inicializa_arvore();
  verde = inicializa_arvore();
  especial = inicializa_arvore();


 // Declaração e inicialização das pilhas
    tp_pilha red, blue, yellow, green, curingas, baralho;
    tp_cartas e, i;
    tp_pilha mesa;

    inicializa_pilha(&red);
    inicializa_pilha(&blue);
    inicializa_pilha(&yellow);
    inicializa_pilha(&green);
    inicializa_pilha(&curingas);
    inicializa_pilha(&baralho);
    inicializa_pilha(&mesa);

    // Inicialização das cartas e empilhamento no baralho
    inicializa_cartas(&red, 'R');
    inicializa_cartas(&blue, 'B');
    inicializa_cartas(&yellow, 'Y');
    inicializa_cartas(&green, 'G');
    inicializa_curingas(&curingas, 'E');
    empilha_pilhas(&baralho, &blue);
    empilha_pilhas(&baralho, &red);
    empilha_pilhas(&baralho, &yellow);
    empilha_pilhas(&baralho, &green);
    empilha_pilhas(&baralho, &curingas);

  fprintf (uno, "Cartas inicializadas\n");

    // Embaralhamento do baralho
    embaralha_cartas(&baralho);
    embaralha_cartas(&baralho);
    embaralha_cartas(&baralho);
    embaralha_cartas(&baralho);
    embaralha_cartas(&baralho);
    embaralha_cartas(&baralho);
    embaralha_cartas(&baralho);
    embaralha_cartas(&baralho);

  fprintf (uno, "Cartas embaralhadas\n");

    do {
      pop(&baralho, &e);
      if (e.cor == 'E' || e.num == 10 || e.num == 11 || e.num == 12) {
        push(&baralho, e);
        embaralha_cartas(&baralho);
      }
    } while (e.cor == 'E');

    push(&mesa, e);




  tp_listad *mao_jogador1 = inicializa_listad(); 
  tp_listad *mao_jogador2 = inicializa_listad(); 
  distribui_cartas(&baralho, mao_jogador1, mao_jogador2);

    fprintf (uno, "Mãos dos jogadores criadas e preenchidas\n");


    fprintf (uno, "Jogo iniciado\n");
    system("clear");
 top(&mesa, &i);
    printf("                                         10E -----> Bloqueio\n");
    printf("                                         11E -----> +2\n");
    printf("                                         12E -----> Inverter Ordem\n");
    printf("                                         13E -----> Escolher Cor\n");
    printf("                                         14E -----> +4\n");




    printf("       __________\n");
    printf("      |          |\n");
    printf("      |          |\n");

    switch (i.cor) {
        case 'R':
            printf("      |    %s%d %c%s    |\n", vvermelho, i.num, i.cor, resett);
            break;
        case 'B':
            printf("      |    %s%d %c%s    |\n", azzul, i.num, i.cor, resett);
            break;
        case 'Y':
            printf("      |    %s%d %c%s    |\n", amarello, i.num, i.cor, resett);
            break;
        case 'G':
            printf("      |    %s%d %c%s    |\n", vverde, i.num, i.cor, resett);
            break;
        case 'E':
            printf("      |    %s%d %c%s    |\n", roxxo, i.num, i.cor, resett);
            break;
        default:
            printf("      |    %d %c    |\n", i.num, i.cor);
            break;
    }

    printf("      |          |\n");
    printf("      |          |\n");
    printf("      |__________|\n");

  printf("\n \n");














// while((vazio(*mao_jogador1)!=1) && (vazio(*mao_jogador2)!=1)){
  while(1){


printf("\nMão do jogador %s: \n", jogador1);
imprime_listad(mao_jogador1, 1);
printf("\n");

joga_cartas(mao_jogador1, e, &mesa, &baralho, jogador1, mao_jogador2, jogador2, &verde, &amarelo, &vermelho, &especial, &azul);
  system("clear");


top(&mesa, &i);
      fprintf (uno, "Jogada de %s: %d %c :\n",jogador1,i.num, i.cor);
    printf("                                         10E -----> Bloqueio\n");
    printf("                                         11E -----> +2\n");
    printf("                                         12E -----> Inverter Ordem\n");
    printf("                                         13E -----> Escolher Cor\n");
    printf("                                         14E -----> +4\n");




    printf("       __________\n");
    printf("      |          |\n");
    printf("      |          |\n");

    switch (i.cor) {
        case 'R':
            printf("      |    %s%d %c%s    |\n", vvermelho, i.num, i.cor, resett);
            break;
        case 'B':
            printf("      |    %s%d %c%s    |\n", azzul, i.num, i.cor, resett);
            break;
        case 'Y':
            printf("      |    %s%d %c%s    |\n", amarello, i.num, i.cor, resett);
            break;
        case 'G':
            printf("      |    %s%d %c%s    |\n", vverde, i.num, i.cor, resett);
            break;
        case 'E':
            printf("      |    %s%d %c%s    |\n", roxxo, i.num, i.cor, resett);
            break;
        default:
            printf("      |    %d %c    |\n", i.num, i.cor);
            break;
    }

    printf("      |          |\n");
    printf("      |          |\n");
    printf("      |__________|\n");

  printf("\n \n");
  if(vazio(*mao_jogador1)==1){
    printf(" %s venceu!!", jogador1);
    break;
    fprintf (uno, "%s VENCEU\n",jogador1);
    fclose(uno);
  }


  printf("\nMão do jogador %s: \n", jogador2);
  imprime_listad(mao_jogador2, 1);
  printf("\n");




    joga_cartas(mao_jogador2, e, &mesa, &baralho, jogador2, mao_jogador1, jogador1, &verde, &amarelo, &vermelho, &especial, &azul );
    system("clear");
    top(&mesa, &i);
        fprintf (uno, "Jogada de %s: %d %c :\n",jogador2,i.num, i.cor);
   printf("                                         10E -----> Bloqueio\n");
    printf("                                         11E -----> +2\n");
    printf("                                         12E -----> Inverter Ordem\n");
    printf("                                         13E -----> Escolher Cor\n");
    printf("                                         14E -----> +4\n");




    printf("       __________\n");
    printf("      |          |\n");
    printf("      |          |\n");

    switch (i.cor) {
        case 'R':
            printf("      |    %s%d %c%s    |\n", vvermelho, i.num, i.cor, resett);
            break;
        case 'B':
            printf("      |    %s%d %c%s    |\n", azzul, i.num, i.cor, resett);
            break;
        case 'Y':
            printf("      |    %s%d %c%s    |\n", amarello, i.num, i.cor, resett);
            break;
        case 'G':
            printf("      |    %s%d %c%s    |\n", vverde, i.num, i.cor, resett);
            break;
        case 'E':
            printf("      |    %s%d %c%s    |\n", roxxo, i.num, i.cor, resett);
            break;
        default:
            printf("      |    %d %c    |\n", i.num, i.cor);
            break;
    }

    printf("      |          |\n");
    printf("      |          |\n");
    printf("      |__________|\n");

  printf("\n \n");
  if(vazio(*mao_jogador2)==1){
    printf(" %s Venceu!!", jogador2);
    fprintf (uno, "%s VENCEU\n",jogador2);
     fclose(uno);
    break;
  }
}

  fclose(uno);
  return 0;
}