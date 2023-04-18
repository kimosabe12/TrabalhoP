//
// Created by diogo on 04/04/2023.
//

#include "headers.h"

void adicionar_linha(Linha** linhas, int* n_linhas, Paragem* paragens, int n_paragens) {
    char nome_linha[50];
    printf("Insira o nome da nova linha: ");
    scanf("%s", nome_linha);
    fflush(stdin);
    nome_linha[strlen(nome_linha)] = '\0';

    // Verificar se a linha já existe
    if (existe_linha(*linhas, *n_linhas, nome_linha)) {
        printf("Ja existe uma linha com o nome %s.\n", nome_linha);
        return;
    }

    // código para solicitar ou ler informações da nova linha
    int n_paragens_linha;
    printf("Quantas paragens tem a nova linha? ");
    scanf("%d", &n_paragens_linha);

    Paragem** paragens_linha = (Paragem**) malloc(n_paragens_linha * sizeof(Paragem*));
    for (int i = 0; i < n_paragens_linha; i++) {
        char codigo[50];
        printf("Insira o codigo da paragem %d da nova linha: ", i+1);
        scanf("%s", codigo);

        // Procurar a paragem correspondente na matriz de paragens
        int index = -1;
        for (int j = 0; j < n_paragens; j++) {
            if (strcmp(paragens[j].codigo, codigo) == 0) {
                index = j;
                break;
            }
        }

        if (index == -1) {
            printf("Nao foi encontrada nenhuma paragem com o codigo %s.\n", codigo);
            return;
        }

        paragens_linha[i] = &paragens[index];
    }

    // Criar a nova linha e adicioná-la à lista ligada
    Linha* nova_linha = (Linha*) malloc(sizeof(Linha));
    strcpy(nova_linha->nome, nome_linha);
    nova_linha->paragens = paragens_linha;
    nova_linha->n_paragens = n_paragens_linha;
    nova_linha->prox = NULL;

    if (*linhas == NULL) {
        *linhas = nova_linha;
    } else {
        Linha* temp = *linhas;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = nova_linha;
    }
    (*n_linhas)++;
}
int existe_linha(Linha* linhas, int n_linhas, char* nome) {
    for (int i = 0; i < n_linhas; i++) {
        if (strcmp(linhas[i].nome, nome) == 0) {
            return 1; // retorna 1 se já existe uma linha com esse nome
        }
    }
    return 0; // retorna 0 se não existe uma linha com esse nome
}
void visualizar_linhas(Linha* linhas) {
    if (linhas == NULL) {
        printf("Nao ha linhas registadas.\n");
        return;
    }
    printf("Linhas existentes no sistema:\n");

    Linha* temp = linhas;
    while (temp != NULL) {
        printf("Nome: %s\n", temp->nome);
        printf("Numero de paragens: %d\n", temp->n_paragens);
        printf("Paragens:\n");
        for (int j = 0; j < temp->n_paragens; j++) {
            printf("- %s\n", temp->paragens[j]->nome);
        }

        printf("\n");
        temp = temp->prox;
    }
}


void atualiza_linha(Linha* linha, Paragem* paragens, int n_paragens) {



    char codigo[5];
    int index;
    printf("Indique o codigo da paragem que pretender adicionar a linha: ");
    scanf("%4s", codigo);
    // Procurar a paragem correspondente na matriz de paragens
    index= procurar_paragem_por_codigo(paragens, n_paragens,codigo);
    printf("Sai da funcao procurar paragem por codigo");
    if(index==-1){
        printf("Nao foi encontrada nenhuma paragem com o codigo %s.\n", codigo);
        return;
    }

    // Procurar a linha correspondente na matriz de linhas
    //Apesar de ja ter garantido que ela existe, temos de armazenar o indice da linha

    printf("A adicionar");
    // Adiciona a nova paragem à lista ligada de paragens da linha encontrada
    linha->paragens= realloc(linha->paragens, (++linha->n_paragens)*sizeof(Paragem*));
    if(linha->paragens==NULL){
        printf("Erro!");
        return;
    }

    linha->paragens[linha->n_paragens-1]=&paragens[index];

    printf("Linha atualizada com sucesso!\n");
}


