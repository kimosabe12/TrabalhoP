//
// Created by diogo on 04/04/2023.
//Diogo Valente Soares - 2020144110
//

#include "headers.h"

void adicionar_linha(Linha** linhas, int* n_linhas, Paragem* paragens, int n_paragens) {
    char nome_linha[50];
    printf("Insira o nome da nova linha: ");
    fgets(nome_linha, 50, stdin);
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
    if(n_paragens_linha==0){
        printf("Nao pode existir uma linha com 0 paragens! \n");
        return;
    }


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
    int contador = 0;
    Linha* temp_1 = linhas;
    while (temp_1 != NULL) {
        contador++;
        temp_1 = temp_1->prox;
    }
    if(contador==0){
        printf("\nNao existem linhas no sistema");
    }else {
        printf("Linhas existentes no sistema: %d\n", contador);
    }
    Linha* temp_2 = linhas;
    while (temp_2 != NULL) {
        printf("Nome: %s\n", temp_2->nome);
        printf("Numero de paragens: %d\n", temp_2->n_paragens);
        printf("Paragens:\n");
        for (int j = 0; j < temp_2->n_paragens; j++) {
            printf("- %s\n", temp_2->paragens[j]->nome);
        }

        printf("\n");
        temp_2 = temp_2->prox;
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

void remove_paragem_linha(Linha* linha, Paragem* paragens, int n_paragens) {
    char codigo[5];
    int index;
    printf("Indique o codigo da paragem que pretende remover da linha: ");
    scanf("%4s", codigo);
    // Procurar a paragem correspondente na matriz de paragens
    index = procurar_paragem_por_codigo(paragens, n_paragens,codigo);
    if(index == -1){
        printf("Nao foi encontrada nenhuma paragem com o codigo %s.\n", codigo);
        return;
    }
    // Procurar a paragem na lista ligada de paragens da linha
    for (int i = 0; i < linha->n_paragens; i++) {
        if (linha->paragens[i] == &paragens[index]) {
            // Remover a paragem da lista ligada
            for (int j = i; j < linha->n_paragens - 1; j++) {
                linha->paragens[j] = linha->paragens[j + 1];
            }
            linha->n_paragens--;
            linha->paragens = realloc(linha->paragens, linha->n_paragens * sizeof(Paragem*));
            printf("Paragem removida com sucesso!\n");
            return;
        }
    }
    printf("A paragem com o codigo %s nao foi encontrada na linha.\n", codigo);
}


void adiciona_linha_txt(Linha** linhas, int *n_linhas,Paragem* paragens, int n_paragens){
    FILE *ficheiro;
    char nome_linha[50];
    char codigo[5];
    ficheiro= fopen("nova_linha.txt","r");
    if(ficheiro==NULL){
        printf("Erro ao abrir o ficheiro");
    }
    fgets(nome_linha, 50, ficheiro);
    nome_linha[strlen(nome_linha) - 1]='\0';
    if (existe_linha(*linhas, *n_linhas, nome_linha)) {
        printf("Ja existe uma linha com o nome %s.\n", nome_linha);
        return;
    }
    // Criar a nova linha
    Linha* nova_linha = (Linha*) malloc(sizeof(Linha));
    strcpy(nova_linha->nome, nome_linha);
    nova_linha->paragens = NULL;
    nova_linha->n_paragens = 0;
    nova_linha->prox = NULL;

    // Ler as paragens da linha

    int n_paragens_linha = 0;
    int i = 0;
    int encontrou_hashtag = 0;
    int paragem_existe = 0;
    Paragem* p;
    while (1) {
        int c = fgetc(ficheiro);
        if (c == '#') {
            encontrou_hashtag = 1;
        } else if (c == '\n' || c == EOF) {
            if (encontrou_hashtag) {
                codigo[i] = '\0';
                i = 0;
                encontrou_hashtag = 0;
                paragem_existe = 0;
                for (int j = 0; j < n_paragens; j++) {
                    if (strcmp(paragens[j].codigo, codigo) == 0) {
                        p = &paragens[j];
                        paragem_existe = 1;
                        break;
                    }
                }
                if (!paragem_existe) {
                    printf("Nao foi encontrada nenhuma paragem com o codigo %s.\n", codigo);
                    fclose(ficheiro);
                    return;
                }
                nova_linha->paragens = (Paragem**) realloc(nova_linha->paragens, (nova_linha->n_paragens + 1) * sizeof(Paragem*));
                nova_linha->paragens[nova_linha->n_paragens] = p;
                nova_linha->n_paragens++;
            }
            if (c == EOF) {
                break;
            }
            n_paragens_linha++;
        } else if (encontrou_hashtag) {
            codigo[i++] = (char) c;
        }
    }

    // Adicionar a nova linha à lista ligada
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
    printf("\nA linha foi adicionada com sucesso");

}

int paragem_pertence_a_linha(Linha* linhas, char* codigo) {
    Linha* linha_atual = linhas;
    while (linha_atual != NULL) {
        for (int i = 0; i < linha_atual->n_paragens; i++) {
            if (strcmp(linha_atual->paragens[i]->codigo, codigo) == 0) {
                return 1;
            }
        }
        linha_atual = linha_atual->prox;
    }
    return 0;
}
/*

Linha* encontrar_linha_por_paragens(Linha* linhas, Paragem* partida, Paragem* chegada) {
    Linha* linha_atual = linhas;
    while (linha_atual != NULL) {
        int encontrou_partida = 0;
        int encontrou_chegada = 0;
        for (int i = 0; i < linha_atual->n_paragens; i++) {
            Paragem* paragem_atual = *(linha_atual->paragens + i);
            if (strcmp(paragem_atual->codigo, partida->codigo) == 0) {
                encontrou_partida = 1;
            }
            if (strcmp(paragem_atual->codigo, chegada->codigo) == 0) {
                encontrou_chegada = 1;
            }
        }
        if (encontrou_partida && encontrou_chegada) {
            return linha_atual;
        }
        linha_atual = linha_atual->prox;
    }
    return NULL; // Não foi encontrada nenhuma linha que ligue a partida e a chegada
}

*/

Etapa* encontrar_caminho(Linha* linhas, Paragem* partida, Paragem* chegada, int* n_etapas) {
    *n_etapas = 0;
    Linha* linha_atual = linhas;
    while (linha_atual != NULL) {
        int encontrou_partida = 0;
        int indice_partida = -1;
        for (int i = 0; i < linha_atual->n_paragens; i++) {
            Paragem* paragem_atual = *(linha_atual->paragens + i);
            if (strcmp(paragem_atual->codigo, partida->codigo) == 0) {
                encontrou_partida = 1;
                indice_partida = i;
                break;
            }
        }
        if (encontrou_partida) {
            Linha* linha_atual2 = linhas;
            while (linha_atual2 != NULL) {
                int encontrou_chegada = 0;
                int indice_chegada = -1;
                for (int i = 0; i < linha_atual2->n_paragens; i++) {
                    Paragem* paragem_atual = *(linha_atual2->paragens + i);
                    if (strcmp(paragem_atual->codigo, chegada->codigo) == 0) {
                        encontrou_chegada = 1;
                        indice_chegada = i;
                        break;
                    }
                }
                if (encontrou_chegada) {
                    for (int i = 0; i < linha_atual->n_paragens; i++) {
                        Paragem* paragem_atual = *(linha_atual->paragens + i);
                        for (int j = 0; j < linha_atual2->n_paragens; j++) {
                            Paragem* paragem_atual2 = *(linha_atual2->paragens + j);
                            if (strcmp(paragem_atual->codigo, paragem_atual2->codigo) == 0) {
                                Etapa* etapas = (Etapa*) malloc(2 * sizeof(Etapa));
                                etapas[0].linha = linha_atual;
                                etapas[0].n_paragens = i - indice_partida + 1;
                                etapas[0].paragens = (Paragem**) malloc(etapas[0].n_paragens * sizeof(Paragem*));
                                for (int k = 0; k < etapas[0].n_paragens; k++) {
                                    etapas[0].paragens[k] = *(linha_atual->paragens + indice_partida + k);
                                }
                                etapas[1].linha = linha_atual2;
                                etapas[1].n_paragens = indice_chegada - j + 1;
                                etapas[1].paragens = (Paragem**) malloc(etapas[1].n_paragens * sizeof(Paragem*));
                                for (int k = 0; k < etapas[1].n_paragens; k++) {
                                    etapas[1].paragens[k] = *(linha_atual2->paragens + j + k);
                                }
                                *n_etapas = 2;
                                return etapas;
                            }
                        }
                    }
                }
                linha_atual2 = linha_atual2->prox;
            }
        }
        linha_atual = linha_atual->prox;
    }
    return NULL;
}
