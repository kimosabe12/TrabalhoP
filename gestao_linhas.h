//
// Created by diogo on 04/04/2023.
//

#ifndef TRABALHOP_GESTAO_LINHAS_H
#define TRABALHOP_GESTAO_LINHAS_H
typedef struct linha Linha;
struct linha {
    char nome[50];
    int n_paragens;
    Paragem* paragens;
    Linha* prox;
};
void adicionar_linha(Linha** linhas, int* n_linhas, Paragem* paragens, int n_paragens);
int existe_linha(Linha* linhas, int n_linhas, char* nome);
void visualizar_linhas(Linha* linhas);
#endif //TRABALHOP_GESTAO_LINHAS_H
