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
                       /* char nome_linha[50];
                        char code[5];
                        FILE* ficheiro_2 = fopen("nova_linha.txt", "r");
                        if(ficheiro_2 == NULL) {
                            printf("Erro ao abrir o ficheiro!\n");
                            return 1;
                        }else{
                           // fscanf(ficheiro_2,)
                        }
                        // Lê o nome da nova linha
                        char nome_linha[50];
                        if(fgets(nome_linha, 50, ficheiro) == NULL) {
                            printf("Erro ao ler o nome da linha!\n");
                            return 1;
                        }

                        nome_linha[strcspn(nome_linha, "\n")] = '\0';
                        */
                        adiciona_linha_txt(&linhas, &n_linhas, paragens, n_paragens);
                    }
                } else if(opcao4==2){
                    char nome[50];
                    printf("\nDigite o nome da linha que deseja atualizar: ");
                    scanf("%49[^\n]%*c", nome);

                    for (int i = 0; i < n_linhas; i++) {
                        if (strcmp(linhas[i].nome, nome) == 0) {
                            int opcao_atualiza;
                            printf("\nDeseja adicionar ou remover uma paragem? ");
                            printf("\n1-Adicionar");
                            printf("\n2-Remover");
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

                }else{
                    printf("\nOpcao Invalida");
                }
                break;
            }
            case 5: {
                printf("\nOpcao de Sair escolhida");
                int opcao5;
                printf("\nDeseja guardar as paragens criadas?");
                printf("\n1-Sim");
                printf("\n2-Nao");
                scanf("\n%d", &opcao5);
                if(opcao5==1){
                    ficheiro = fopen("metro.bin", "wb");
                    if(ficheiro == NULL) {
                        printf("Erro ao abrir o ficheiro!\n");
                        return 1;
                    }
                    // escrever o número de paragens e a matriz de paragens
                    fwrite(&n_paragens, sizeof(int), 1, ficheiro);
                    fwrite(paragens, sizeof(Paragem), n_paragens, ficheiro);

                    return 0;
                }else {
                    return 0;
                }

            }
        }
        }
    // fechar o ficheiro
    //fclose(ficheiro);

        return 0;
}
