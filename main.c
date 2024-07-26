#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define MAX_ITENS 100

typedef struct {
    char codigo[11];      // Código da Motocicleta
    char marca[15];       // Marca da moto
    char modelo[15];      // modelo do veiculo
    char placa[9];        // placa do veiculo
    char quilometragem;   // quillometragem da moto
    char cilindrada;      // capacidade do motor
    char cor[10];         // cor do veiculo
    float ano;            // ano da moto
    float valor;          // Valor do produto
    char habilitado;      // Indicador de habilitação do produto ('S' para habilitado, 'N' para desabilitado)
    int posVetor;         // Posição do produto no vetor
}Produto;

Produto Produtos[MAX_ITENS];    // Vetor de produtos
int iQtdRegistros = 0;           // Quantidade de registros de produtos


int main() {
    int opcao;

    FILE *fArquivo = fopen("produtos.txt", "r");
    if (fArquivo != NULL) {
        printf("Lendo arquivo de dados: produtos.txt\n");
        fscanf(fArquivo, "%d\n", &iQtdRegistros);
        printf("%d registros encontrados.\n\n", iQtdRegistros); // mostra numero de motos registradas

        for (int i = 0; i < iQtdRegistros; i++) {
            fscanf(fArquivo, "%s %s %s %s %s %s %s %f %f %s\n", Produtos[i].codigo, Produtos[i].placa, Produtos[i].marca, Produtos[i].modelo, Produtos[i].cilindrada, Produtos[i].cor, &Produtos[i].ano, &Produtos[i].valor, Produtos[i].quilometragem);
            Produtos[i].habilitado = 'S';
            Produtos[i].posVetor = i;
        }
        fclose(fArquivo);
    } else {
        printf("O arquivo produtos.txt nao foi localizado, criando novo arquivo.\n\n"); // se n�o tiver o arquivo criado
        fArquivo = fopen("produtos.txt", "a+");}

    do {

        /* Impress�o do Menu + loop */
        printf("Sistema de Gerenciamento da Papelaria\n");
        printf("--------------------------------------\n\n");


        printf("1- Cadastrar produto\n");
        printf("2- Editar produto\n");
        printf("3- Excluir produto\n");
        printf("4- Buscar produto\n");
        printf("5- Listar produtos\n");
        printf("6- Estatisticas do sistema\n");
        printf("7- Sair\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1:
                cadastrar_produto();
                break;
            case 2:
                editar_produto();
                break;
            case 3:
                excluir_produto();
                break;
            case 4:
                buscar_Produto();
                break;
            case 5:
                listar_Produto();
                break;
            case 6:
                estatisticas_Sistema();
                break;
            case 7:
                grava_arquivo();
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
        }

        printf("\n<enter> para reiniciar\n");
        getchar(); // Lê o caractere "Enter" do buffer do teclado
        getchar(); // Aguarda o usuário pressionar a tecla "Enter"

    } while (opcao != 7);

    return 0;
}

void cadastrar_produto(){
    printf("1");

}

void editar_produto(){
     printf("2");
}
void excluir_produto(){
     printf("3");

}
void buscar_Produto(){
     printf("4");

}
void listar_Produto(){
     printf("5");

}
void estatisticas_Sistema() {
     printf("6");

}
void grava_arquivo(){
    printf("7");
}









