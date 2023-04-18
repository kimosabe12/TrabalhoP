//
// Created by diogo on 04/04/2023.
//

#ifndef TRABALHOP_PARAGENS_H
#define TRABALHOP_PARAGENS_H
typedef struct {
    char nome[50];
    char codigo[5];
} Paragem;
void gerar_codigo_aleatorio(char* codigo);
void registar_paragem(Paragem** paragens, int* n_paragens);
void remover_paragem(Paragem** paragens, int* n_paragens);
void visualizar_paragens(Paragem* paragens, int n_paragens);
int procurar_paragem_por_codigo(Paragem* paragens, int n_paragens, char* codigo);
#endif //TRABALHOP_PARAGENS_H
