#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da constante para o tamanho máximo do acervo
#define TAMANHO_ACERVO 20

// Definição da struct Livro
struct Livro {
    int codigo;
    char titulo[50];
    char autor[30];
    char area[30];
    int ano;
    char editora[30];
};

// Protótipos das Funções
void menuPrincipal();
void cadastrarLivros(struct Livro acervo[], int *totalLivros);
void imprimirLivros(struct Livro acervo[], int totalLivros);
void pesquisarLivro(struct Livro acervo[], int totalLivros);
void ordenarLivros(struct Livro acervo[], int totalLivros);
void limparBuffer();

// Função principal
int main() {
    struct Livro acervo[TAMANHO_ACERVO];
    int totalLivros = 0;
    int opcao;

    do {
        menuPrincipal();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarLivros(acervo, &totalLivros);
                break;
            case 2:
                imprimirLivros(acervo, totalLivros);
                break;
            case 3:
                pesquisarLivro(acervo, totalLivros);
                break;
            case 4:
                ordenarLivros(acervo, totalLivros);
                break;
            case 5:
                printf("\nSaindo do programa. Ate mais!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
        printf("\nPressione ENTER para continuar...");
        getchar();
        // system("cls"); // Descomente para limpar a tela em sistemas Windows
        // system("clear"); // Descomente para limpar a tela em sistemas Linux/Mac
    } while (opcao != 5);

    return 0;
}

// Implementação da função auxiliar para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Implementação do menuPrincipal
void menuPrincipal() {
    printf("\n--- SISTEMA DE GERENCIAMENTO DE LIVROS ---\n");
    printf("1 - Cadastrar livros\n");
    printf("2 - Imprimir todos os livros\n");
    printf("3 - Pesquisar livro por codigo\n");
    printf("4 - Ordenar livros por ano de publicacao\n");
    printf("5 - Sair do programa\n");
    printf("------------------------------------------\n");
}

// Implementação da função cadastrarLivros
void cadastrarLivros(struct Livro acervo[], int *totalLivros) {
    if (*totalLivros >= TAMANHO_ACERVO) {
        printf("\nERRO: Acervo cheio! Limite de %d livros atingido.\n", TAMANHO_ACERVO);
        return;
    }

    printf("\n--- CADASTRO DE NOVO LIVRO ---\n");
    int i = *totalLivros;
    
    printf("Codigo do Livro: ");
    scanf("%d", &acervo[i].codigo);
    limparBuffer();

    printf("Titulo: ");
    fgets(acervo[i].titulo, 50, stdin);
    acervo[i].titulo[strcspn(acervo[i].titulo, "\n")] = 0;

    printf("Autor: ");
    fgets(acervo[i].autor, 30, stdin);
    acervo[i].autor[strcspn(acervo[i].autor, "\n")] = 0;

    printf("Area: ");
    fgets(acervo[i].area, 30, stdin);
    acervo[i].area[strcspn(acervo[i].area, "\n")] = 0;

    printf("Ano de Publicacao: ");
    scanf("%d", &acervo[i].ano);
    limparBuffer();

    printf("Editora: ");
    fgets(acervo[i].editora, 30, stdin);
    acervo[i].editora[strcspn(acervo[i].editora, "\n")] = 0;

    (*totalLivros)++;
    printf("\nLivro cadastrado com sucesso! Total de livros: %d\n", *totalLivros);
}

// Implementação da função imprimirLivros
void imprimirLivros(struct Livro acervo[], int totalLivros) {
    if (totalLivros == 0) {
        printf("\nAcervo vazio. Cadastre livros primeiro.\n");
        return;
    }

    printf("\n--- ACERVO COMPLETO (%d livros) ---\n", totalLivros);
    for (int i = 0; i < totalLivros; i++) {
        printf("\n[LIVRO %d]\n", i + 1);
        printf("  Codigo: %d\n", acervo[i].codigo);
        printf("  Titulo: %s\n", acervo[i].titulo);
        printf("  Autor: %s\n", acervo[i].autor);
        printf("  Area: %s\n", acervo[i].area);
        printf("  Ano: %d\n", acervo[i].ano);
        printf("  Editora: %s\n", acervo[i].editora);
    }
    printf("------------------------------------------\n");
}

// Implementação da função pesquisarLivro
void pesquisarLivro(struct Livro acervo[], int totalLivros) {
    if (totalLivros == 0) {
        printf("\nAcervo vazio. Cadastre livros primeiro.\n");
        return;
    }

    int codigoBusca;
    int encontrado = 0;
    
    printf("\n--- PESQUISAR LIVRO POR CODIGO ---\n");
    printf("Digite o codigo do livro que deseja buscar: ");
    scanf("%d", &codigoBusca);
    limparBuffer();

    for (int i = 0; i < totalLivros; i++) {
        if (acervo[i].codigo == codigoBusca) {
            printf("\nLIVRO ENCONTRADO!\n");
            printf("  Codigo: %d\n", acervo[i].codigo);
            printf("  Titulo: %s\n", acervo[i].titulo);
            printf("  Autor: %s\n", acervo[i].autor);
            printf("  Area: %s\n", acervo[i].area);
            printf("  Ano: %d\n", acervo[i].ano);
            printf("  Editora: %s\n", acervo[i].editora);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nERRO: Livro com codigo %d nao encontrado no acervo.\n", codigoBusca);
    }
}

// Implementação da função ordenarLivros (Bubble Sort)
void ordenarLivros(struct Livro acervo[], int totalLivros) {
    if (totalLivros <= 1) {
        printf("\nNao ha livros suficientes para ordenar.\n");
        return;
    }

    struct Livro temp;

    for (int i = 0; i < totalLivros - 1; i++) {
        for (int j = 0; j < totalLivros - 1 - i; j++) {
            // Compara os anos de publicação
            if (acervo[j].ano > acervo[j+1].ano) {
                // Realiza a troca (swap)
                temp = acervo[j];
                acervo[j] = acervo[j+1];
                acervo[j+1] = temp;
            }
        }
    }
    printf("\nAcervo ordenado com sucesso por Ano de Publicacao (do mais antigo para o mais novo).\n");
}
