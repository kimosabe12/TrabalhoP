//
// Created by diogo on 04/04/2023.
//Diogo Valente Soares - 2020144110
//

#include "headers.h"
void gerar_codigo_aleatorio(char* codigo) {
    const char caracteres[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int n_caracteres = strlen(caracteres);
    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
        codigo[i] = caracteres[rand() % n_caracteres];
    }
    codigo[4] = '\0';
}


void registar_paragem(Paragem** paragens, int* n_paragens) {
    *paragens = realloc(*paragens, (*n_paragens + 1) * sizeof(Paragem));
    if (*paragens == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    int i;
    char nome[100];
    do {

        printf("Digite o nome da paragem: ");
        scanf("%99[^\n]%*c", nome);

        // Verifica se já existe uma paragem com o mesmo nome
        for (i = 0; i < *n_paragens; i++) {
            if (strcmp((*paragens)[i].nome, nome) == 0) {
                printf("Já existe uma paragem com o nome '%s'. Digite um nome diferente.\n", nome);
                break;
            }
        }
    } while (i < *n_paragens); // Repete o loop enquanto o nome já existir

    strcpy((*paragens)[*n_paragens].nome, nome); // Copia o nome da nova paragem para a estrutura

    // Gera um código aleatório para a paragem
    gerar_codigo_aleatorio((*paragens)[*n_paragens].codigo);

    // Imprime o código da nova paragem
    printf("Paragem adicionada com sucesso. Codigo: %s\n", (*paragens)[*n_paragens].codigo);


    (*n_paragens)++;
}

void remover_paragem(Paragem** paragens, int* n_paragens) {
    char codigo[5];
    int index;
    if (*n_paragens < 2) {
        printf("Erro: a matriz de paragens nao pode ser reduzida para zero.\n");
        return;
    }

    // Solicitar o código da paragem a ser removida
    printf("Digite o codigo da paragem a ser removida novamente: ");
    scanf("%4s", codigo);

    // Procurar a paragem correspondente na matriz de paragens
    index = procurar_paragem_por_codigo(*paragens, *n_paragens, codigo);
    if (index == -1) {
        printf("Nao foi encontrada nenhuma paragem com o codigo %s.\n", codigo);
        return;
    }

    /*
    // Procurar a paragem correspondente na matriz de paragens
    for (int i = 0; i < *n_paragens; i++) {
        if (strcmp((*paragens)[i].codigo, codigo) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Nao foi encontrada nenhuma paragem com o codigo %s.\n", codigo);
        return;
    }
*/
    // Deslocar as paragens na matriz após a paragem a ser removida um índice para trás
    for (int i = index; i < *n_paragens - 1; i++) {
        (*paragens)[i] = (*paragens)[i + 1];
    }

    // Realocar a matriz de paragens para liberar a memória alocada para a paragem removida
    *n_paragens = *n_paragens - 1;
    *paragens = realloc(*paragens, (*n_paragens) * sizeof(Paragem));
    if (*paragens == NULL) {
        printf("Erro: falha na realocacao de memoria.\n");
        exit(1);
    }

    printf("Paragem com o codigo %s removida com sucesso.\n", codigo);

}


void visualizar_paragens(Paragem* paragens, int n_paragens) {
    if (n_paragens == 0) {
        printf("Nao ha paragens para visualizar.\n");
        return;
    }
    printf("Lista de Paragens:\n");
    for (int i = 0; i < n_paragens; i++) {
        printf("Codigo: %s | Nome: %s\n", paragens[i].codigo, paragens[i].nome);
    }
}

int procurar_paragem_por_codigo(Paragem* paragens, int n_paragens, char* codigo) {
    for (int i = 0; i < n_paragens; i++) {
        if (strcmp(paragens[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1;
}
