#ifndef PILHA_h
#define PILHA_h
#include <stdio.h>
#define MAX_PILHA 110
#include "types.h"
// typedef int tp_item;
// variável de tamanho do vetor. foi feita outra structure para essa variável
// pra n especificar o tipo da variável

typedef struct {
  int topo; // variavel para mostrar o topo
  tp_cartas item[MAX_PILHA];
} tp_pilha;

// inicializa pilha
void inicializa_pilha(tp_pilha *p) { // passagem de parâmetro por ponteiro
  p->topo = -1; // p apontando para topo e declarando seu valor como -1
}

int pilha_vazia(tp_pilha *p) {
  if (p->topo == -1)
    return 1; // valor do topo definido como -1 = pilha vazia.
  else
    return 0; // caso n esteja vazia, retorna 0.
}

// verificando se a pilha ta cheia

int pilha_cheia(tp_pilha *p) {
  if (p->topo == MAX_PILHA - 1) {
    return 1; // pilha de 100 elementos, de 0 a 99, ou seja, se o topo for
              // 100-1(99) a pilha está cheia, retorna 1
  } else {
    return 0; // pilha não está cheia, retorna 0
  }
}

int push(tp_pilha *p, tp_cartas e) {
  if (pilha_cheia(p))
    return 0; // pilha possui espaço
  p->topo++;  //índice do topo aumenta 1 para novo conteúdo
  p->item[p->topo] =
      e; // valor de e guardado dentro de item na posição que o topo indica
  return 1;
}

int pop(tp_pilha *p,
        tp_cartas
            *e) { // primeiro parâmetro = pilha, segundo parâmetro endereço de e
  if (pilha_vazia(p) == 1)
    return 0;
  *e = p->item[p->topo]; // e recebe o valor da variável do topo da lista
  p->topo--;             // diminui um índice do topo
  return 1;
}

int top(tp_pilha *p, tp_cartas *e) {
  if (pilha_vazia(p))
    return 0;

  *e = p->item[p->topo];
  return 1;
}

int altura_pilha(tp_pilha *p) { return p->topo + 1; }

void imprime_pilha(tp_pilha p) {
  tp_cartas e;
  printf("deck:\n");
  while (!pilha_vazia(&p)) {
    pop(&p, &e);
    printf("%d %c\n", e.num, e.cor);
  }
}



int empilha_pilhas(tp_pilha *p1, tp_pilha *p2) {
  tp_cartas e;
  tp_pilha paux;
  inicializa_pilha(&paux);
  if (altura_pilha(p1) + altura_pilha(p2) > MAX_PILHA)
    return 0;
  while (!pilha_vazia(p2)) {
    pop(p2, &e);
    push(&paux, e);
  }
  while (!pilha_vazia(&paux)) {
    pop(&paux, &e);
    push(p1, e);
  }

  return 1;
}

void iguala_pilhas(tp_pilha *p1, tp_pilha *p2) {
  tp_cartas topo;
  int tamanho1 = altura_pilha(p1);
  int tamanho2 = altura_pilha(p2);
  int i = 0;
  int j = 0;
  pop(p1, &topo);
  inicializa_pilha(p1);
  inicializa_pilha(p2);
  while (i != tamanho1) {
    push(p1, topo);
    i++;
  }
  while (j != tamanho2) {
    push(p2, topo);
    j++;
  }
}


#endif