//
// Created by diogo on 04/04/2023.
//

#ifndef TRABALHOP_GESTAO_LINHAS_H
#define TRABALHOP_GESTAO_LINHAS_H

typedef struct linha Linha;
struct linha {
    char nome[50];
    int n_paragens;
    Paragem** paragens;
    Linha* prox;
};

void adicionar_linha(Linha** linhas, int* n_linhas, Paragem* paragens, int n_paragens);
int existe_linha(Linha* linhas, int n_linhas, char* nome);
void visualizar_linhas(Linha* linhas);
void atualiza_linha(Linha* linha, Paragem* paragens, int n_paragens);
void remove_paragem_linha(Linha* linha, Paragem* paragens, int n_paragens);
void adicionar_paragem(Linha* linha, Paragem* paragem);
void adiciona_linha_txt(Linha** linhas, int *n_linhas,Paragem* paragens, int n_paragens);
int paragem_pertence_a_linha(Linha* linhas, char* codigo);
#endif //TRABALHOP_GESTAO_LINHAS_H
