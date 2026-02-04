//Prática: SISTEMA DE BIBLIOTECA

//Objetivo: Implementar o cadstro e a listagem de livros usando um array estático.
//Foco em structs, entrada/saída de dados e organização básica.

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Para strcspn()

// Constantes Globais
#define MAX_LIVROS 50
#define TAM_STRING 100

// Definição da Estrutura
typedef struct {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
} Livro;

// Função para limpar o buffer de entrada
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(){
    Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    // Laço Principal do Menu
    do{
        //exibição do menu
        printf("================================\n");
        printf("    Biblioteca\n");
        printf("================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("0 - Sair\n");
        printf("--------------------------------\n");
        printf("Escolha uma opcao: \n");

        //Lê a opção do usuário
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf.

        //Processamento da opção
        switch (opcao){
            case 1: //cadastro de novo livro
                printf("--- Cadastro de Novo Livro ---\n\n");

                if (totalLivros < MAX_LIVROS){
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING,stdin);

                    printf("Digite a editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                    printf("Digite a edicao: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBufferEntrada();

                    totalLivros++;

                    printf("\nLivro cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia!! Nao e possivel cadastrar mais livros.\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            
            case 2: //Listagem de livros
                printf("--- Lista de livros cadastrados ---\n\n");

                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda..\n");
                } else {
                    for (int i = 0; i < totalLivros; i++){
                        printf("-----------------------------------\n");
                        printf("Livro %d\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edicao: %d\n", biblioteca[i].edicao);
                    }
                    printf("-------------------------------------\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 0: //Sair
                printf("\nSaindo do sistema...\n");
                break;
            
            default: //Opção inválida
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        }   
    } while (opcao != 0);

    return 0;

}