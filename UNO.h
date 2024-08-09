#ifndef UNO_h
#define UNO_h
#include <stdio.h>
#include <unistd.h>
#define MAX_CARTAS 110
#define MAX_JOGADORES 2
#include "arvorebb.h"
#include "listade.h"
#include "pilha.h"
#include "types.h"
#include <stdlib.h>
#include <time.h>

void inicializa_cartas(tp_pilha *baralho, char cor) {

  // A função "inicializa_cartas" é declarada com dois parâmetros: um ponteiro
  // para uma variável do tipo "tp_pilha" chamada "baralho" e um inteiro chamado
  // "cor".

  for (int i = 0; i <= 9; i++) {
    baralho->item[i].num = i;
    baralho->item[i].cor = cor;
    baralho->topo++;
  }

  // Esse laço inicializa as cartas numeradas de 0 a 9, com a cor especificada
  // como parâmetro para a função. A variável i varia de 0 a 9, e para cada
  // valor de i, o número da carta é definido como i, a cor é definida como a
  // cor especificada como parâmetro, e o topo da pilha é incrementado.

  for (int i = 1; i <= 9; i++) {
    baralho->item[i + 9].num = i;
    baralho->item[i + 9].cor = cor;
    baralho->topo++;
  }

  // O segundo laço for inicializa as cartas numeradas de 1 a 9, com a mesma cor
  // especificada como parâmetro para a função. A variável i varia de 1 a 9, e
  // para cada valor de i, o número da carta é definido como i, a cor é definida
  // como a cor especificada como parâmetro, e o topo da pilha é incrementado.

  for (int i = 1; i <= 2; i++) { // Cartas de Bloqueio
    baralho->item[i + 18].num = 10;
    baralho->item[i + 18].cor = cor;
    baralho->topo++;
  }
  for (int i = 1; i <= 2; i++) { // Cartas de +2 para cada cor
    baralho->item[i + 20].num = 11;
    baralho->item[i + 20].cor = cor;
    baralho->topo++;
  }
  for (int i = 1; i <= 2; i++) { // Carta de inverter sentido do jogo (inverte)
    baralho->item[i + 22].num = 12;
    baralho->item[i + 22].cor = cor;
    baralho->topo++;
  }
}

void inicializa_curingas(tp_pilha *baralho, char s) {
  for (int i = 0; i < 4; i++) { // carta de escolher cor
    baralho->item[i].num = 13;
    baralho->item[i].cor = s;
    baralho->topo++;
  }

  for (int i = 4; i < 8; i++) { // carta de +4
    baralho->item[i].num = 14;
    baralho->item[i].cor = s;
    baralho->topo++;
  }
}

// O primeiro laço for percorre o índice de 0 a 3 e atribui à cada uma das 4
// primeiras cartas da pilha, um número 13 representando a carta de escolher cor
// e a cor s recebida como parâmetro. A variável topo da estrutura tp_pilha é
// incrementada para indicar que uma nova carta foi adicionada à pilha.

// O segundo laço for percorre o índice de 4 a 7 e atribui à cada uma das 4
// últimas cartas da pilha, um número 14 representando a carta de escolher cor e
// +4 e a cor s recebida como parâmetro. Novamente, a variável topo é
// incrementada para indicar que uma nova carta foi adicionada à pilha.

// Ao final da execução da função, a pilha terá sido inicializada com 8 cartas
// curingas, 4 para escolha de cor e 4 para escolha de cor e adição de 4 cartas
// na mão do próximo jogador.

void embaralha_cartas(tp_pilha *baralho) {
  tp_pilha aux;
  tp_pilha aux2;
  tp_pilha aux3;
  tp_cartas e;

  inicializa_pilha(&aux);
  inicializa_pilha(&aux2);
  inicializa_pilha(&aux3);

  srand(time(NULL));
  while (!pilha_vazia(baralho)) {
    int num = (rand() % 3) + 1;
    if (num == 1) {
      pop(baralho, &e);
      push(&aux, e);
    } else if (num == 2) {
      pop(baralho, &e);
      push(&aux2, e);
    } else if (num == 3) {
      pop(baralho, &e);
      push(&aux3, e);
    }
  }
  while (!pilha_vazia(&aux)) {
    pop(&aux, &e);
    push(baralho, e);
  }
  while (!pilha_vazia(&aux2)) {
    pop(&aux2, &e);
    push(baralho, e);
  }
  while (!pilha_vazia(&aux3)) {
    pop(&aux3, &e);
    push(baralho, e);
  }
}

/*
 São inicializadas as três pilhas auxiliares (aux, aux2 e aux3) utilizando a
função "inicializa_pilha". Utilizamos o comando "srand(time(NULL))" para
inicializar o gerador de números aleatórios, que será utilizado para sortear a
ordem das cartas na pilha.

Dessa forma, se o número sorteado for igual a 1, a carta no topo da pilha
"baralho" é removida utilizando a função "pop" e adicionada à pilha auxiliar
"aux" utilizando a função "push" e assim sucessivamente para o numero 2 e 3.
Depois que todas as cartas forem distribuidas,cada pilha auxiliar é percorrida
com um laço de repetição "while", removendo as cartas do topo da pilha
utilizando a função "pop" e adicionando-as novamente na pilha "baralho"
utilizando a função "push".


No final a pilha "baralho" estará com as cartas totalmente embaralhadas e de
forma aleatória
*/

void distribui_cartas(tp_pilha *baralho, tp_listad *mao_jogador1,
                      tp_listad *mao_jogador2) {
  tp_cartas carta;
  for (int i = 0; i < 7; i++) {
    pop(baralho, &carta);
    insere_listad_fim(mao_jogador1, carta);
  }
  for (int i = 0; i < 7; i++) {
    pop(baralho, &carta);
    insere_listad_fim(mao_jogador2, carta);
  }
}

void insere_nas_arvores(tp_arvore *vermelho, tp_arvore *azul,
                        tp_arvore *amarelo, tp_arvore *verde,
                        tp_arvore *especiais, tp_cartas e) {
  if (e.cor == 'R')
    insere_no(vermelho, e);
  else if (e.cor == 'B')
    insere_no(azul, e);
  else if (e.cor == 'Y')
    insere_no(amarelo, e);
  else if (e.cor == 'G')
    insere_no(verde, e);
  else if (e.cor == 'E')
    insere_no(especiais, e);
  else
    printf("Essa cor nao existe\n");
}

void procura_cartas(tp_arvore vermelho, tp_arvore azul, tp_arvore amarelo,
                    tp_arvore verde, tp_arvore especiais) {
  int num;
  char cor;
  tp_item e;
  printf("Qual carta deseja procurar\n");
  scanf("%d %c", &num, &cor);

  e.cor = cor;
  e.num = num;
  int achou = 0;

  switch (e.cor) {
  case 'R':
    achou = busca_no(vermelho, e);
    if (achou == 1) {
      printf("A carta já foi jogada\n");
    } else {
      printf("Esta carta nunca foi jogada\n");
    }
    break;

  case 'B':
    achou = busca_no(azul, e);
    if (achou == 1) {
      printf("A carta já foi jogada\n");
    } else {
      printf("Esta carta nunca foi jogada\n");
    }
    break;

  case 'G':
    achou = busca_no(verde, e);
    if (achou == 1) {
      printf("A carta já foi jogada\n");
    } else {
      printf("Esta carta nunca foi jogada\n");
    }
    break;

  case 'Y':
    achou = busca_no(amarelo, e);
    if (achou == 1) {
      printf("A carta já foi jogada\n");
    } else {
      printf("Esta carta nunca foi jogada\n");
    }
    break;

  case 'E':
    achou = busca_no(especiais, e);
    if (achou == 1) {
      printf("A carta já foi jogada\n");
    } else {
      printf("Esta carta nunca foi jogada\n");
    }
    break;

  default:
    printf("Selecione uma cor válida");
    break;
  }
}

tp_listad *joga_cartas(tp_listad *mao_jogador1, tp_cartas e, tp_pilha *mesa,
                       tp_pilha *baralho, char jogador1[21],
                       tp_listad *mao_jogador2, char jogador2[21],
                       tp_arvore *verde, tp_arvore *amarelo,
                       tp_arvore *vermelho, tp_arvore *especial,
                       tp_arvore *azul) {
  char *vermelhao = "\033[0;31m";
  char *reset = "\033[0m";
  char *rosa = "\033[38;5;206m";
  char *roxo = "\033[38;5;129m";
  char *vermelhinho = "\033[0;31m";
  tp_cartas g;

  int fim = 1;
  while (fim == 1) {
    if (pilha_vazia(baralho)) {
      printf("O baralho está vazio. As cartas da mesa serão realocadas e o "
             "baralho será embaralhado.\n");
      pop(mesa, &e);
      g = e;
      while (!pilha_vazia(mesa)) {
        pop(mesa, &e);
        push(baralho, e);
      }
      push(mesa, g);
      embaralha_cartas(baralho);
      embaralha_cartas(baralho);
      embaralha_cartas(baralho);
      embaralha_cartas(baralho);
      embaralha_cartas(baralho);
      embaralha_cartas(baralho);
      embaralha_cartas(baralho);
      embaralha_cartas(baralho);
    }

    printf("\nEscolha um número e uma cor para jogar / Digite %s1K%s para "
           "cavar / Digite %s1P%s para pesquisar se uma carta já foi jogada\n",
           rosa, reset, roxo, reset);
    scanf(" %d %c", &e.num, &e.cor);

    if (e.cor != 'K' && e.cor != 'P' && busca_listad(mao_jogador1, e) == NULL) {
      // printf("Carta Inválida\n",vermelhinho,reset); //ver se a carta está na
      // mão do jogador
      printf("\033[91mCarta Inválida\033[0m\n");
      fim = 1;
    } else if (e.cor == 'P') { // procurar as cartas
      procura_cartas(*vermelho, *azul, *amarelo, *verde, *especial);
      fim = 1;
    } else {
      if (e.cor == 'K') { // Lógica para cavar
        tp_cartas aux;
        pop(baralho, &aux);
        insere_listad_fim(mao_jogador1, aux);

        printf("\n\n");
        printf("Mão atualizada:\n");

        imprime_listad(mao_jogador1, 1);
        fim = 1;
      }

      else { // jogar
        top(mesa, &g);
        if (g.cor == e.cor || g.num == e.num || e.cor == 'E') {
          remove_listade(mao_jogador1, e);
          insere_nas_arvores(vermelho, azul, amarelo, verde, especial,
                             e); // gravar cada jogada na arvore
          push(mesa, e);

          if (e.num == 10) { // bloqueio
            remove_listade(mao_jogador1, e);
            insere_nas_arvores(vermelho, azul, amarelo, verde, especial, e);
            push(mesa, e);

            printf("\nVocê bloqueou %s!\nJogue novamente!\n", jogador2);
            printf("       __________\n");
            printf("      |          |\n");
            printf("      |          |\n");
            printf("      |    %d%c", e.num, e.cor);
            printf("    |\n");
            printf("      |          |\n");
            printf("      |          |\n");
            printf("      |__________|\n");
            printf("\n\n");
            printf("Mão do jogador %s\n", jogador1);
            imprime_listad(mao_jogador1, 1);
            fim = 1;
          }

          else if (e.num == 11) { // próximo cava 2
            printf("O jogador %s cava duas cartas!\n", jogador2);
            sleep(2);
            remove_listade(mao_jogador1, e);
            insere_nas_arvores(vermelho, azul, amarelo, verde, especial, e);
            push(mesa, e);

            pop(baralho, &e);
            insere_listad_fim(mao_jogador2, e);
            pop(baralho, &e);
            insere_listad_fim(mao_jogador2, e);

            fim = 0;
          } else if (e.num == 12) { // inverte ordem(como são dois jogadores,
                                    // adaptamos essa carta para quem jogou
                                    // jogar novamente, e o próximo cava 1)

            remove_listade(mao_jogador1, e);
            insere_nas_arvores(vermelho, azul, amarelo, verde, especial, e);
            push(mesa, e);

            printf("A ordem de jogada foi invertida! Jogue novamente, e o "
                   "jogador %s cava 1 carta!\n\n",
                   jogador2);

            printf("       __________\n");
            printf("      |          |\n");
            printf("      |          |\n");
            printf("      |    %d%c", e.num, e.cor);
            printf("    |\n");
            printf("      |          |\n");
            printf("      |          |\n");
            printf("      |__________|\n");
            printf("\n\n");
            printf("Mão do jogador %s\n", jogador1);
            imprime_listad(mao_jogador1, 1);
            pop(baralho, &e);
            insere_listad_fim(mao_jogador2, e);
            fim = 1;

          } else if (e.num == 13) {
            printf("%s, escolha uma cor\n", jogador1);
            char cor;
            scanf(" %c", &cor);

            if (cor == 'B' || cor == 'Y' || cor == 'G' || cor == 'R') {
              remove_listade(mao_jogador1, e);
              insere_nas_arvores(vermelho, azul, amarelo, verde, especial, e);
              e.cor = cor;
              push(mesa, e);
              fim = 0;
            }

          } else if (e.num == 14) {
            tp_cartas save = e;
            printf("%s cava 4 cartas!\n %s, escolha uma cor\n", jogador2,
                   jogador1);
            pop(baralho, &e);
            insere_listad_fim(mao_jogador2, e);
            pop(baralho, &e);
            insere_listad_fim(mao_jogador2, e);
            pop(baralho, &e);
            insere_listad_fim(mao_jogador2, e);
            pop(baralho, &e);
            insere_listad_fim(mao_jogador2, e);
            char cor;
            scanf(" %c", &cor);
            if (cor == 'B' || cor == 'Y' || cor == 'G' || cor == 'R') {
              remove_listade(mao_jogador1, save);
              insere_nas_arvores(vermelho, azul, amarelo, verde, especial,
                                 save);
              save.cor = cor;
              push(mesa, save);
              fim = 0;
            }
          }

          else {
            fim = 0;
          }
        }

        else {
          printf("%sCarta Incompatível com a mesa, tente novamente!%s\n\n",
                 vermelhao, reset);
          fim = 1;
        }
      }
    }
  }
}

#endif