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


    // ler o número de linhas e a lista ligada de linhas
    fread(&n_linhas, sizeof(int), 1, ficheiro);
    for(int i=0; i<n_linhas; i++) {
        Linha* nova_linha = malloc(sizeof(Linha));
        fread(nova_linha, sizeof(Linha), 1, ficheiro);
        nova_linha->prox = linhas;
        linhas = nova_linha;
    }


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
                    remover_paragem(&paragens, &n_paragens);
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
                    adicionar_linha(&linhas, &n_linhas, paragens, n_paragens);
                } else if(opcao4==2){
                    atualiza_linha(&linhas, n_linhas, paragens, n_paragens);
                }
            }
        }
        }
    // escrever o número de paragens e a matriz de paragens
    fwrite(&n_paragens, sizeof(int), 1, ficheiro);
    fwrite(paragens, sizeof(Paragem), n_paragens, ficheiro);

    // escrever o número de linhas e a lista ligada de linhas
    fwrite(&n_linhas, sizeof(int), 1, ficheiro);
    for(Linha* p=linhas; p!=NULL; p=p->prox) {
        fwrite(p, sizeof(Linha), 1, ficheiro);
    }

    // fechar o ficheiro
    fclose(ficheiro);

        return 0;
}
