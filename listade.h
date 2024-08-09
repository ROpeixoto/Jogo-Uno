#ifndef LISTADE_h
#define LISTADE_h

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct tp_no_aux {
tp_cartas info;
struct tp_no_aux *ant;
struct tp_no_aux *prox;
} tp_no;


typedef struct{
tp_no *ini;
tp_no *fim;
}tp_listad;

tp_listad *inicializa_listad (){
  tp_listad *lista=(tp_listad*) malloc(sizeof(tp_listad));
  lista->ini = NULL;
  lista->fim = NULL;

  return lista;
}


tp_no *aloca(){
  tp_no* pt;
  pt = (tp_no*) malloc(sizeof(tp_no));
  return pt;
}

int vazio(tp_listad lista){
  if ((lista.ini == NULL) && (lista.fim == NULL))
  return 1;
  else
  return 0;
}


int insere_listad_fim(tp_listad *lista, tp_cartas e){
  tp_no *novo;
  novo=aloca();
  if(!novo) return 0;
  novo->info = e;
  if ( (lista->ini == NULL) && (lista->fim == NULL)){
    novo->prox = NULL;
    novo->ant = NULL;
    lista->ini = lista->fim = novo;
  }
  else{
    novo->prox = NULL;
    novo->ant = lista->fim;
    lista->fim->prox = novo;
    lista->fim = novo;
  }
  return 1;
}

void imprime_listad(tp_listad *lista, int ordem) {
    tp_no *atu;
    char* cor;

    switch (ordem) {
        case 1:
            atu = lista->ini;
            while (atu != NULL) {
                switch (atu->info.cor) {
                    case 'R':
                        cor = "\033[0;31m"; // Vermelho
                        break;
                    case 'B':
                        cor = "\033[0;34m"; // Azul
                        break;
                    case 'Y':
                        cor = "\033[0;33m"; // Amarelo
                        break;
                    case 'G':
                        cor = "\033[0;38;2;0;255;0m"; // Verde
                        break;
                    case 'E':
                        cor = "\033[0;35m"; // Roxo
                        break;
                    default:
                        cor = "\033[0m"; // Resetar cor
                        break;
                }

                printf("%s %d %c /", cor, atu->info.num, atu->info.cor);
                atu = atu->prox;
            }
            break;

        case 2:
            atu = lista->fim;
            while (atu != NULL) {
                switch (atu->info.cor) {
                    case 'R':
                        cor = "\033[0;31m"; // Vermelho
                        break;
                    case 'B':
                        cor = "\033[0;34m"; // Azul
                        break;
                    case 'Y':
                        cor = "\033[0;33m"; // Amarelo
                        break;
                    case 'G':
                        cor = "\033[0;32m"; // Verde
                        break;
                    case 'E':
                        cor = "\033[0;35m"; // Roxo
                        break;
                    default:
                        cor = "\033[0m"; // Resetar cor
                        break;
                }

                printf("%s %d %c /", cor, atu->info.num, atu->info.cor);
                atu = atu->ant;
            }
            break;

        default:
            printf("Código inválido");
    }

    printf("\033[0m\n"); // Resetar cor
}

int remove_listade(tp_listad *lista, tp_cartas e){
  tp_no *atu;
  atu = lista->ini;

   while ((atu != NULL) && (atu->info.num != e.num || atu->  
 info.cor != e.cor)){
  atu=atu->prox;
   }
  if(atu == NULL) return 0;

  if(lista->ini == lista->fim){
    lista->ini = lista->fim = NULL;}

  else{
    if(lista->ini == atu){
      lista->ini = atu->prox;
      atu->prox->ant=NULL;
    }
      else{
        if(lista->fim == atu){
          lista->fim = atu->ant;
          atu->ant->prox = NULL;
        }

        else{
          atu->prox->ant = atu->ant;
          atu->ant->prox = atu->prox;
        }
        }
        }
  free(atu);

  return 1;
      }

tp_no * busca_listad (tp_listad *lista, tp_cartas e){
  tp_no *atu;
  atu = lista->ini;
  //printf(": %d %c %d %c\n", atu->info.num, atu->info.cor, e.num, e.cor);
  while ( (atu != NULL) && ((atu->info.num != e.num) || (atu->info.cor != e.cor))){
    //printf(".. %d %c %d %c\n", atu->info.num, atu->info.cor, e.num, e.cor);
    atu=atu->prox;}
    //printf("... %d %c \n", atu->info.num, atu->info.cor);

  return atu;
}

int verifica_uno(tp_listad lista) {
  if (lista.ini == lista.fim) {
    return 1;
  } else {
    return 0;
  }
}




#endif