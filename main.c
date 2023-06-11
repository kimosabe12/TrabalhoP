//Diogo Valente Soares - 2020144110
#include <stdio.h>
#include "headers.h"
int main() {
    printf("Bem-Vindo ao Metro Mondego!!\n");

    Paragem* paragens=NULL;
    int n_paragens=0;
    Linha* linhas = NULL;
    int n_linhas = 0;


    // abrir o ficheiro binário para leitura
    FILE* ficheiro = fopen("metro.bin", "rb+");
    if(ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro!\n");
        return 1;
    }
    // ler o número de paragens e a matriz de paragens
    fread(&n_paragens, sizeof(int), 1, ficheiro);
    paragens = malloc(n_paragens * sizeof(Paragem));
    fread(paragens, sizeof(Paragem), n_paragens, ficheiro);

    // ler o número de linhas
    fread(&n_linhas, sizeof(int), 1, ficheiro);
    // usar um loop para ler cada linha
    for (int i = 0; i < n_linhas; i++) {
        // criar uma nova estrutura Linha e inicializar seus campos
        Linha* nova_linha = (Linha*) malloc(sizeof(Linha));
        fread(nova_linha->nome, sizeof(char), 50, ficheiro);
        fread(&nova_linha->n_paragens, sizeof(int), 1, ficheiro);
        nova_linha->paragens = (Paragem**) malloc(nova_linha->n_paragens * sizeof(Paragem*));
        nova_linha->prox = NULL;

        // usar um loop para ler cada paragem da linha
        for (int j = 0; j < nova_linha->n_paragens; j++) {
            Paragem* nova_paragem = (Paragem*) malloc(sizeof(Paragem));
            fread(nova_paragem, sizeof(Paragem), 1, ficheiro);
            nova_linha->paragens[j] = nova_paragem;
        }

        // adicionar a nova linha à lista ligada
        if (linhas == NULL) {
            linhas = nova_linha;
        } else {
            Linha* temp = linhas;
            while (temp->prox != NULL) {
                temp = temp->prox;
            }
            temp->prox = nova_linha;
        }
    }





    fclose(ficheiro);

    int verifica=1;
    while (verifica){
        int opcao=0;
        printf("\n1-Viajar");
        printf("\n2-Editar Paragens");
        printf("\n3-Visualizar Paragens ou Linhas");
        printf("\n4-Gestao das Linhas");
        printf("\n5-Sair");
        printf("\n Escolha uma opcao: ");
        do {
            scanf("%d", &opcao);
            fflush(stdin);
            if (opcao < 0 || opcao > 5)
                printf("\nOpcao invalida");
            if (opcao == 5)
                verifica = 0;
        } while (opcao < 0 || opcao > 5);
        switch (opcao) {
            case 1:{

                    //encontra o caminho ideal para o meu user
                    printf("\nOpcao 1 escolhida\n");
                    char partida_nome[100];
                    char chegada_nome[100];
                    printf("Qual o nome da paragem de partida: ");
                    scanf("%99[^\n]%*c", partida_nome);
                    printf("Qual o nome da paragem de chegada: ");
                    scanf("%99[^\n]%*c", chegada_nome);

                    Paragem* partida = NULL;
                    Paragem* chegada = NULL;

                    // Encontrar a paragem de partida
                    for (int i = 0; i < n_paragens; i++) {
                        if (strcmp(paragens[i].nome, partida_nome) == 0) {
                            partida = &paragens[i];
                            break;
                        }
                    }

                    // Encontrar a paragem de chegada
                    for (int i = 0; i < n_paragens; i++) {
                        if (strcmp(paragens[i].nome, chegada_nome) == 0) {
                            chegada = &paragens[i];
                            break;
                        }
                    }

                    if (partida == NULL) {
                        printf("Paragem de partida nao encontrada.\n");
                        break;
                    }else if(chegada==NULL){
                        printf("Paragem de chegada nnao encontrada");
                        break;
                    }
                    /*
                    Linha* linha_encontrada = encontrar_linha_por_paragens(linhas, partida, chegada);
                    if (linha_encontrada == NULL) {
                        printf("Nao existe uma linha que ligue a paragem de partida e chegada.\n");
                        break;
                    } else {
                        printf("Linha encontrada: %s\n", linha_encontrada->nome);
                        break;
                    }
                */
                int n_etapas;
                Etapa* etapas = encontrar_caminho(linhas, partida, chegada, &n_etapas);
                if (etapas == NULL) {
                    printf("Nao foi encontrado um caminho entre as duas paragens.\n");
                } else {
                    printf("Caminho encontrado:\n");
                    for (int i = 0; i < n_etapas; i++) {
                        printf("Linha: %s\n", etapas[i].linha->nome);
                        for (int j = 0; j < etapas[i].n_paragens; j++) {
                            printf("Paragem: %s\n", etapas[i].paragens[j]->nome);
                        }
                    }
                    printf("Chegada: %s\n", chegada_nome);
                }
                break;
            }
            case 2:{
                printf("\nOpcao 2 escolhida\n");
                int opcao2;
                printf("\nO que pretende fazer?:");
                printf("\n1- Adicionar Paragem");
                printf("\n2- Remover Paragem");
                printf("\nEscolha uma opcao: ");
                scanf("%d", &opcao2);
                fflush(stdin);
                if(opcao2==1){
                    registar_paragem(&paragens, &n_paragens);
                }else if(opcao2==2){
                    char codigo[5];
                    int index;
                    // Solicitar o código da paragem a ser removida
                    printf("Digite o codigo da paragem a ser removida: ");
                    scanf("%4s", codigo);
                    index = procurar_paragem_por_codigo(paragens, n_paragens, codigo);
                    if (index == -1) {
                        printf("Nao foi encontrada nenhuma paragem com o codigo %s.\n", codigo);
                        break;
                    }
                    if(paragem_pertence_a_linha(linhas,codigo)==1){
                        printf("Erro: a paragem com o codigo %s pertence a uma linha e nao pode ser removida.\n", codigo);
                    } else{
                        remover_paragem(&paragens, &n_paragens);

                    }
                } else{
                    printf("Opcao invalida");
                }
                break;
            }
            case 3:{
                printf("\nOpcao 3 escolhida\n");
                int opcao3;
                printf("\nO que pretende fazer?");
                printf("\n1-Visualizar Paragens");
                printf("\n2-Visualizar Linhas");
                printf("\nEscolha uma opcao: ");
                scanf("%d", &opcao3);
                fflush(stdin);
                if(opcao3==1){
                    visualizar_paragens(paragens, n_paragens);
                } else if(opcao3==2){
                    visualizar_linhas(linhas);
                }else{
                    printf("Opcao Invalida");
                }
                break;
            }
            case 4:{
                printf("\nOpcao 4 escolhida\n");
                int opcao4;
                printf("\nO que pretende fazer?");
                printf("\n1-Adicionar uma Nova Linha");
                printf("\n2-Atualizar uma Linha");
                printf("\nEscolha uma opcao: ");
                scanf("%d", &opcao4);
                fflush(stdin);
                if(opcao4==1){
                    int opcao;
                    printf("\n1- Adicionar uma linha manualmente");
                    printf("\n2- Adicionar uma linha atraves de ficheiro de texto");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d", &opcao);
                    fflush(stdin);
                    if(opcao==1) {
                        adicionar_linha(&linhas, &n_linhas, paragens, n_paragens);
                    }else if(opcao==2){
                        adiciona_linha_txt(&linhas, &n_linhas, paragens, n_paragens);
                    }
                } else if(opcao4==2){
                    char nome[50];
                    printf("Insira o nome da linha que deseja atualizar: ");
                    fgets(nome, 50, stdin);
                    nome[strlen(nome)] = '\0';

                    int encontrou_linha = 0;
                    for (int i = 0; i < n_linhas; i++) {

                        if (strcmp(linhas[i].nome, nome) == 0) {
                            encontrou_linha = 1;
                            int opcao_atualiza;
                            printf("\nDeseja adicionar ou remover uma paragem? ");
                            printf("\n1-Adicionar");
                            printf("\n2-Remover");
                            printf("\nEscolha a opcao: ");
                            scanf("%d",&opcao_atualiza);
                            fflush(stdin);
                            if(opcao_atualiza==1){
                                atualiza_linha(&linhas[i], paragens, n_paragens);
                            }else if(opcao_atualiza==2){
                                remove_paragem_linha(&linhas[i], paragens, n_paragens);
                            }else{
                                printf("\nOpcao Invalida!");
                            }
                        }

                    }

                    if (!encontrou_linha) {
                        printf("Nao existem uma linha com esse nome");
                    }
                } else {
                    printf("\nOpcao Invalida");
                }

                break;
            }
            case 5: {
                printf("\nOpcao de Sair escolhida");
                int opcao5;
                printf("\nDeseja guardar as paragens e linhas criadas?");
                printf("\n1-Sim");
                printf("\n2-Nao");
                printf("\nEscolha uma opcao: ");
                scanf("%d", &opcao5);
                if(opcao5==1){
                    ficheiro = fopen("metro.bin", "wb");
                    if(ficheiro == NULL) {
                        printf("Erro ao abrir o ficheiro!\n");
                        return 1;
                    }
                    // escrever o número de paragens e a matriz de paragens
                    fwrite(&n_paragens, sizeof(int), 1, ficheiro);
                    fwrite(paragens, sizeof(Paragem), n_paragens, ficheiro);

                    // escrever o número de linhas
                    fwrite(&n_linhas, sizeof(int), 1, ficheiro);
                    // percorrer a lista ligada de linhas e escrever cada linha
                    Linha* linha_atual = linhas;
                    while (linha_atual != NULL) {
                        // escrever o nome e o número de paragens da linha
                        fwrite(linha_atual->nome, sizeof(char), 50, ficheiro);
                        fwrite(&linha_atual->n_paragens, sizeof(int), 1, ficheiro);

                        // percorrer o vetor de paragens da linha e escrever cada paragem
                        for (int i = 0; i < linha_atual->n_paragens; i++) {
                            Paragem* paragem_atual = *(linha_atual->paragens + i);
                            fwrite(paragem_atual, sizeof(Paragem), 1, ficheiro);
                        }

                        linha_atual = linha_atual->prox;
                    }

// fechar o ficheiro
                    fclose(ficheiro);

                    return 0;
                }else {
                    return 0;
                }

            }
        }
        }


        return 0;
}
