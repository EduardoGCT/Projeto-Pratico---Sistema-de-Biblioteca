//Prática: SISTEMA DE BIBLIOTECA


#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Para strcspn()

// Constantes Globais
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

// Definição da Estrutura
typedef struct {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; //1 pra sim, 0 pra não
} Livro;

// struct para armzenar informações do empréstimo.
typedef struct{
    int indiceLivro; //Para saber qual livro do array 'biblioteca' foi emprestado
    char nomeUsuario[TAM_STRING];
} Emprestimo;


// Protótipos das funções
void limparBufferEntrada();
void exibirMenu();
void cadastrarLivro(Livro *biblioteca, int *totalLivros);
void listarLivros(const Livro *biblioteca, int totalLivros);
void realizarEmprestimo(Livro *biblioteca, int totalLivros, Emprestimo *emprestimos, int *totalEmprestimos);
void listarEmprestimos(const Livro *biblioteca, const Emprestimo *emprestimos, int totalEmprestimos);
void liberarMermoria();

int main(){
    //1. Alocação Dinâmica de Memória
    //agora, em vez de arrays estáticos, usamod ponteiros.
    Livro *biblioteca;
    Emprestimo *emprestimos;

    //calloc para o array de livros. 
    //vantagem: inicializa toda a memória com zeros.
    biblioteca = (Livro *) calloc(MAX_LIVROS, sizeof(Livro));

    //malloc para o array empréstimos.
    emprestimos = (Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(Emprestimo));

    //verificação se a alocação deu certo
    if (biblioteca == NULL || emprestimos == NULL){
        printf("Erro: Falha ao alocar memoria.\n");
        return 1; //retorna 1 para indicar um erro.
    }
    
    int totalLivros = 0, totalEmprestimos = 0, opcao;

    // Laço Principal do Menu
    do{
        //exibição do menu
        exibirMenu();

        //Lê a opção do usuário
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf.

        //Processamento da opção
        switch (opcao){
            case 1: //cadastro de novo livro
                cadastrarLivro(biblioteca, &totalLivros);
                break;
            
            case 2: //Listagem de livros
                listarLivros(biblioteca, totalLivros);
                break;

            case 3: //realizar empréstimo
                realizarEmprestimo(biblioteca, totalLivros, emprestimos, &totalEmprestimos);
                break;

            case 4: //listar empréstimos
                listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
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

    //2 Liberação de memória
    free(biblioteca);
    free(emprestimos);

    printf("Memoria liberada com sucesso.\n");

    return 0;

}


//Declarando funções

// Função para limpar o buffer de entrada
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//exibir menu
void exibirMenu(){
    printf("================================\n");
        printf("    Biblioteca\n");
        printf("================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Realizar emprestimo\n");
        printf("4 - Listar emprestimos\n");
        printf("0 - Sair\n");
        printf("--------------------------------\n");
        printf("Escolha uma opcao: \n");
}

/**
 * @brief Cadastra um novo livro.
 * @param biblioteca o array de livro
 * @param totalLivros ponteiro para contador de livros, para que seja atualizado
 */
void cadastrarLivro(Livro *biblioteca, int *totalLivros){
    printf("--- Cadastro de Novo Livro ---\n\n");

                if (*totalLivros < MAX_LIVROS){
                    int indice = *totalLivros; // usa o valor apontado pelo ponteiro

                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[indice].nome, TAM_STRING, stdin);

                    printf("Digite o autor: ");
                    fgets(biblioteca[indice].autor, TAM_STRING,stdin);

                    printf("Digite a editora: ");
                    fgets(biblioteca[indice].editora, TAM_STRING, stdin);

                    biblioteca[indice].nome[strcspn(biblioteca[indice].nome, "\n")] = '\0';
                    biblioteca[indice].autor[strcspn(biblioteca[indice].autor, "\n")] = '\0';
                    biblioteca[indice].editora[strcspn(biblioteca[indice].editora, "\n")] = '\0';

                    printf("Digite a edicao: ");
                    scanf("%d", &biblioteca[indice].edicao);
                    limparBufferEntrada();
                    
                    //ao cadastrar, o livro automaticamente se torna disponível.
                    biblioteca[indice].disponivel = 1;

                    (*totalLivros)++;//parenteses para incrementar o valor da variavel na main

                    printf("\nLivro cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia!! Nao e possivel cadastrar mais livros.\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar();
}

/**
 * @brief Lista todos os livros cadastrados.
 * @param biblioteca O array (ponteiro constante)
 * @param totalLivros o número de livros(passagem por valor)
 */
void listarLivros(const Livro *biblioteca, int totalLivros){
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
}

/**
 * @brief Realiza o empréstimo de um livro.
 * @param biblioteca array de livros (modificavel para alterar o status).
 * @param totalLivros total de livros.
 * @param emprestimos array de empréstimos(modificavel).
 * @param totalEmprestimos ponteiro para o contador de emprestimos.
 */
void realizarEmprestimo(Livro *biblioteca, int totalLivros, Emprestimo *emprestimos, int *totalEmprestimos){
    printf("--- Realizar Emprestimo ---\n\n");

    if(*totalEmprestimos >= MAX_EMPRESTIMOS){
        printf("Limite de emprestimos atingido!\n");
    } else{
        printf("Livros disponiveis:\n");
        int disponiveis = 0;
        for (int i = 0; i < totalLivros; i++){
            if(biblioteca[i].disponivel){
                printf("%d - %s\n", i + 1, biblioteca[i].nome);
                disponiveis++;
            }
        }
        
        if (disponiveis == 0){
            printf("Nenhum livro disponivel para emprestimo.\n");
        } else {
            printf("\nDigite o numero do livro que deseja emprestar: ");
            int numLivro;
            scanf("%d", &numLivro);
            limparBufferEntrada();

            int indice = numLivro - 1; //converte para o índice do array (0 a n-1).

            //validação da escolha do usuário.
            if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel){
                printf("Digite o nome do usuario que esta pegando o livro: ");
                fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                emprestimos[*totalEmprestimos].nomeUsuario[strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")] = '\0';

                //registra o empréstimo
                emprestimos[*totalEmprestimos].indiceLivro = indice; 

                //atualiza o status do livro para indisponível
                biblioteca[indice].disponivel = 0;

                (*totalEmprestimos)++;
                printf("\nEmprestimo realizado com sucesso!\n");

            } else {
                printf("\nNumero de livr invalido ou livro indisponivel.\n");
            }
        }
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}

/**
 * @brief Lista todos os empréstimos realizados.
 * @param biblioteca array de livros(leitura).
 * @param emprestimos Array de empréstimos(leitura).
 * @param totalEmprestimos total de empréstimos(valor).
 */
void listarEmprestimos(const Livro *biblioteca, const Emprestimo *emprestimos, int totalEmprestimos){
    printf("--- Lista de Emprestimos ---\n\n");
                if(totalEmprestimos == 0){
                    printf("Nenhum emprestimo realizado.\n");
                } else {
                    for(int i = 0; i < totalEmprestimos; i++){
                        //Usa o índice armazenado no empréstimo para buscar o nome do livro.
                        int indiceLivro = emprestimos[i].indiceLivro;
                        printf("----------------------------------\n");
                        printf("Emprestimo %d\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
                    }
                    printf("--------------------------------------\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar();
}