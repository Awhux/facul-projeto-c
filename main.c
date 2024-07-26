/**
 * @file main.c - Sistema cadastro de motos.c
 * @author <<AUTORES>>
 * @date 2024-07-26
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

// -=-=-=-=-=-= System specifics =-=-=-=-=-=
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
// -=-=-=-=-=-= End of system specifics =-=-=-=-=-=

// -=-=-=-=-=-= Constants =-=-=-=-=-=
#define MAX_MOTORBIKES 100
#define MAX_STRING 50
#define MAX_PLATE 10
// -=-=-=-=-=-= End of constants =-=-=-=-=-=

// -=-=-=-=-=-= Structures =-=-=-=-=-=
struct Motorbike
{
    int code;
    char plate[MAX_PLATE];
    char brand[MAX_STRING];
    char model[MAX_STRING];
    int year;
};

struct Database
{
    struct Motorbike motorbikes[MAX_MOTORBIKES];
    int totalCount;
};
// -=-=-=-=-=-= End of structures =-=-=-=-=-=

// -=-=-=-=-=-=-= Functions =-=-=-=-=-=-=
void clearScreen();
void pauseExecution();
void loadDatabase(struct Database *bd);
void saveDatabase(struct Database *bd);
void showMenu();
void createMotorbike(struct Database *bd);
void editMotorbike(struct Database *bd);
void removeMotorbike(struct Database *bd);
void getAllMotorbikes(struct Database *bd);
void searchMotorbike(struct Database *bd);
void showUsage();
void restartDatabase(struct Database *bd);
// -=-=-=-=-=-=-= End of functions =-=-=-=-=-=-=

/**
 * Função principal do programa.
 * Ela carrega a base de dados, exibe o menu e solicita a escolha do usuário.
 * Dependendo da escolha, ela chama a função correspondente para realizar a operação.
 * O programa continua solicitando e executando operações até que o usuário escolha sair.
 * A base de dados é salva no final do programa.
 *
 * @return int - Código de saída do programa.
 */
int main()
{
    // Define o idioma para português
    setlocale(LC_ALL, "Portuguese");

    // Cria uma estrutura para armazenar a base de dados
    struct Database bd = {0};

    // Variável para armazenar a escolha do usuário
    int escolha;

    // Carrega a base de dados
    loadDatabase(&bd);

    // Loop para solicitar e executar operações até que o usuário escolha sair
    do
    {
        // Limpa a tela
        clearScreen();

        // Exibe o menu
        showMenu();

        // Solicita a escolha do usuário
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        getchar(); // Consome a nova linha

        // Limpa a tela
        clearScreen();

        // Executa a operação correspondente à escolha do usuário
        switch (escolha)
        {
        case 1:
            // Adiciona uma nova moto à base de dados
            createMotorbike(&bd);
            break;
        case 2:
            // Edita uma moto existente na base de dados
            editMotorbike(&bd);
            break;
        case 3:
            // Remove uma moto da base de dados
            removeMotorbike(&bd);
            break;
        case 4:
            // Exibe todas as motos na base de dados
            getAllMotorbikes(&bd);
            break;
        case 5:
            // Busca uma moto na base de dados
            searchMotorbike(&bd);
            break;
        case 6:
            // Exibe o uso do programa
            showUsage();
            break;
        case 7:
            // Reinicia a base de dados
            restartDatabase(&bd);
            break;
        case 0:
            // Sai do programa
            break;
        default:
            // Exibe mensagem de erro e pausa a execução
            printf("Escolha inválida. Por favor, tente novamente.\n");
            pauseExecution();
        }
    } while (escolha != 0);

    // Salva a base de dados no final do programa
    saveDatabase(&bd);

    // Retorna o código de saída do programa
    return 0;
}

/**
 * Limpa a tela do console. Essa função serve para limpar a tela do
 * console, seja no Windows ou no Unix. Ela verifica qual o sistema
 * operacional em que está sendo executada e invoca o comando
 * apropriado para limpar a tela.
 *
 * No Windows, o comando para limpar a tela é "cls".
 *
 * No Unix, o comando para limpar a tela é "clear".
 */
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * Pausa a execução do programa até que o usuário pressione Enter.
 */
void pauseExecution()
{
    printf("\nPressione Enter para continuar...");
    getchar();
}

/**
 * Carrega a base de dados do arquivo 'database.txt'.
 * Se o arquivo não existir, cria um novo.
 * Se o arquivo for inacessível, encerra o programa.
 *
 * A função abre o arquivo "database.txt" para leitura usando a função fopen().
 * Se a abertura falhar (arquivo == NULL), ela tenta criar um novo arquivo
 * vazio. Se a criação falhar, a função encerra o programa.
 *
 * Em seguida, a função lê os dados do arquivo usando a função fscanf(). A
 * função lê os dados linha por linha e armazena-os na estrutura de dados
 * "bd", que representa a base de dados. A cada leitura bem-sucedida, a variável
 * "totalCount" é incrementada.
 *
 * A leitura é encerrada quando a função fscanf() retorna um valor diferente de
 * 5, o que indica o fim do arquivo ou uma linha mal formada.
 *
 * Por fim, a função fecha o arquivo usando a função fclose() e a função retorna.
 */
void loadDatabase(struct Database *bd)
{
    // Abre o arquivo "database.txt" para leitura
    FILE *arquivo = fopen("database.txt", "r");

    // Se a abertura falhou, tenta criar um novo arquivo vazio
    if (arquivo == NULL)
    {
        arquivo = fopen("database.txt", "w");
        if (arquivo == NULL)
        {
            // Se a criação falhou, encerra o programa
            printf("Erro: Não foi possível acessar database.txt\n");
            exit(1);
        }
        fclose(arquivo);
        return;
    }

    // Lê os dados do arquivo e armazena-os na estrutura de dados "bd"
    while (fscanf(arquivo, "%d,%[^,],%[^,],%[^,],%d\n",
                  &bd->motorbikes[bd->totalCount].code,
                  bd->motorbikes[bd->totalCount].plate,
                  bd->motorbikes[bd->totalCount].brand,
                  bd->motorbikes[bd->totalCount].model,
                  &bd->motorbikes[bd->totalCount].year) == 5)
    {
        bd->totalCount++;
    }

    // Fecha o arquivo
    fclose(arquivo);
}

/**
 * Salva a base de dados no arquivo 'database.txt'.
 */
void saveDatabase(struct Database *bd)
{
    FILE *arquivo = fopen("database.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro: Não foi possível salvar a base de dados.\n");
        return;
    }

    for (int i = 0; i < bd->totalCount; i++)
    {
        fprintf(arquivo, "%d,%s,%s,%s,%d\n",
                bd->motorbikes[i].code,
                bd->motorbikes[i].plate,
                bd->motorbikes[i].brand,
                bd->motorbikes[i].model,
                bd->motorbikes[i].year);
    }

    fclose(arquivo);
}

/**
 * Exibe as opções do menu principal.
 */
void showMenu()
{
    printf("========================================\n");
    printf("   Sistema de Gerenciamento de Motos    \n");
    printf("========================================\n");
    printf("1. Adicionar uma moto\n");
    printf("2. Editar uma moto\n");
    printf("3. Excluir uma moto\n");
    printf("4. Listar todas as motos\n");
    printf("5. Pesquisar uma moto\n");
    printf("6. Mostrar uso\n");
    printf("7. Reiniciar base de dados\n");
    printf("0. Sair\n");
    printf("========================================\n");
}

/**
 * Adiciona uma nova moto à base de dados.
 * Valida a entrada do usuário e reinicia se a validação falhar.
 */
void createMotorbike(struct Database *bd)
{
    // Verifica se já atingiu o limite máximo de motos
    if (bd->totalCount >= MAX_MOTORBIKES)
    {
        // Exibe mensagem de erro e pausa a execução
        printf("Erro: Base de dados cheia.\n");
        pauseExecution();
        return;
    }

    // Cria uma nova estrutura para armazenar os dados da moto
    struct Motorbike novaMoto;
    char entrada[MAX_STRING];

    // Loop para validar a entrada do usuário
    while (1)
    {
        // Limpa a tela
        clearScreen();

        // Exibe o cabeçalho do menu
        printf("=== Adicionar Nova Moto ===\n\n");

        // Solicita o código da moto
        printf("Digite o código da moto: ");
        if (scanf("%d", &novaMoto.code) != 1)
        {
            // Exibe mensagem de erro e pausa a execução
            printf("Entrada inválida. Por favor, digite um número.\n");
            while (getchar() != '\n')
                ;
            pauseExecution();
            // Continua o loop para validar a entrada
            continue;
        }
        getchar(); // Consumir nova linha

        // Solicita a placa da moto
        printf("Digite a placa (ex: ABC-1234): ");
        fgets(novaMoto.plate, sizeof(novaMoto.plate), stdin);
        novaMoto.plate[strcspn(novaMoto.plate, "\n")] = 0;

        // Solicita a marca da moto
        printf("Digite a marca: ");
        fgets(novaMoto.brand, sizeof(novaMoto.brand), stdin);
        novaMoto.brand[strcspn(novaMoto.brand, "\n")] = 0;

        // Solicita o modelo da moto
        printf("Digite o modelo: ");
        fgets(novaMoto.model, sizeof(novaMoto.model), stdin);
        novaMoto.model[strcspn(novaMoto.model, "\n")] = 0;

        // Solicita o ano da moto
        printf("Digite o ano: ");
        if (scanf("%d", &novaMoto.year) != 1)
        {
            // Exibe mensagem de erro e pausa a execução
            printf("Entrada inválida. Por favor, digite um número.\n");
            while (getchar() != '\n')
                ;
            pauseExecution();
            // Continua o loop para validar a entrada
            continue;
        }
        getchar(); // Consumir nova linha

        // Validação básica dos dados da moto
        if (novaMoto.code <= 0 || novaMoto.year < 1885 || novaMoto.year > 2100)
        {
            // Exibe mensagem de erro e pausa a execução
            printf("Entrada inválida. Por favor, tente novamente.\n");
            pauseExecution();
            // Continua o loop para validar a entrada
            continue;
        }

        // Encerra o loop de validação
        break;
    }

    // Adiciona a nova moto à base de dados
    bd->motorbikes[bd->totalCount++] = novaMoto;

    // Exibe mensagem de sucesso
    printf("\nMoto adicionada com sucesso.\n");

    // Pausa a execução
    pauseExecution();
}

/**
 * Edita uma moto existente na base de dados.
 */
void editMotorbike(struct Database *bd)
{
    int codigo;
    printf("=== Editar Moto ===\n\n");
    printf("Digite o código da moto a ser editada: ");
    scanf("%d", &codigo);
    getchar(); // Consumir nova linha

    for (int i = 0; i < bd->totalCount; i++)
    {
        if (bd->motorbikes[i].code == codigo)
        {
            clearScreen();
            printf("=== Editando Moto (Código: %d) ===\n\n", codigo);

            printf("Placa atual: %s\n", bd->motorbikes[i].plate);
            printf("Digite a nova placa (ou pressione enter para manter a atual): ");
            char entrada[MAX_STRING];
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = 0;
            if (strlen(entrada) > 0)
                strcpy(bd->motorbikes[i].plate, entrada);

            printf("Marca atual: %s\n", bd->motorbikes[i].brand);
            printf("Digite a nova marca (ou pressione enter para manter a atual): ");
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = 0;
            if (strlen(entrada) > 0)
                strcpy(bd->motorbikes[i].brand, entrada);

            printf("Modelo atual: %s\n", bd->motorbikes[i].model);
            printf("Digite o novo modelo (ou pressione enter para manter o atual): ");
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = 0;
            if (strlen(entrada) > 0)
                strcpy(bd->motorbikes[i].model, entrada);

            printf("Ano atual: %d\n", bd->motorbikes[i].year);
            printf("Digite o novo ano (ou 0 para manter o atual): ");
            int ano;
            scanf("%d", &ano);
            getchar(); // Consumir nova linha
            if (ano != 0)
                bd->motorbikes[i].year = ano;

            printf("\nMoto atualizada com sucesso.\n");
            pauseExecution();
            return;
        }
    }

    printf("Moto não encontrada.\n");
    pauseExecution();
}

/**
 * Exclui uma moto da base de dados.
 */
void removeMotorbike(struct Database *bd)
{
    int codigo;
    printf("=== Excluir Moto ===\n\n");
    printf("Digite o código da moto a ser excluída: ");
    scanf("%d", &codigo);
    getchar(); // Consumir nova linha

    for (int i = 0; i < bd->totalCount; i++)
    {
        if (bd->motorbikes[i].code == codigo)
        {
            printf("\nTem certeza que deseja excluir esta moto? (s/n): ");
            char confirmar;
            scanf(" %c", &confirmar);
            getchar(); // Consumir nova linha

            if (tolower(confirmar) == 's')
            {
                for (int j = i; j < bd->totalCount - 1; j++)
                {
                    bd->motorbikes[j] = bd->motorbikes[j + 1];
                }
                bd->totalCount--;
                printf("\nMoto excluída com sucesso.\n");
            }
            else
            {
                printf("\nExclusão cancelada.\n");
            }
            pauseExecution();
            return;
        }
    }

    printf("Moto não encontrada.\n");
    pauseExecution();
}

/**
 * Exibe todas as motos na base de dados.
 */
void getAllMotorbikes(struct Database *bd)
{
    printf("=== Todas as Motos ===\n\n");
    if (bd->totalCount == 0)
    {
        printf("Não há motos na base de dados.\n");
        pauseExecution();
        return;
    }

    printf("%-6s %-10s %-15s %-15s %-6s\n", "Código", "Placa", "Marca", "Modelo", "Ano");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < bd->totalCount; i++)
    {
        printf("%-6d %-10s %-15s %-15s %-6d\n",
               bd->motorbikes[i].code,
               bd->motorbikes[i].plate,
               bd->motorbikes[i].brand,
               bd->motorbikes[i].model,
               bd->motorbikes[i].year);
    }
    pauseExecution();
}

/**
 * Pesquisa uma moto por código ou placa.
 */
void searchMotorbike(struct Database *bd)
{
    char pesquisa[MAX_STRING];
    printf("=== Pesquisar Moto ===\n\n");
    printf("Digite o código ou a placa para pesquisar: ");
    fgets(pesquisa, sizeof(pesquisa), stdin);
    pesquisa[strcspn(pesquisa, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < bd->totalCount; i++)
    {
        if (atoi(pesquisa) == bd->motorbikes[i].code || strcmp(pesquisa, bd->motorbikes[i].plate) == 0)
        {
            if (!encontrado)
            {
                printf("\nResultados da Pesquisa:\n");
                printf("--------------------------------------------------\n");
            }
            printf("Código: %d\nPlaca: %s\nMarca: %s\nModelo: %s\nAno: %d\n",
                   bd->motorbikes[i].code,
                   bd->motorbikes[i].plate,
                   bd->motorbikes[i].brand,
                   bd->motorbikes[i].model,
                   bd->motorbikes[i].year);
            printf("--------------------------------------------------\n");
            encontrado = 1;
        }
    }

    if (!encontrado)
    {
        printf("\nNenhuma moto correspondente encontrada.\n");
    }
    pauseExecution();
}

/**
 * Mostra o uso da base de dados.
 */
void showUsage()
{
    printf("=== Uso da Base de Dados ===\n\n");
    printf("- A base de dados é armazenada em 'database.txt'\n");
    printf("- Cada linha representa uma moto com o formato: código,placa,marca,modelo,ano\n");
    printf("- A base de dados é carregada quando o programa inicia e salva quando ele é encerrado\n");
    printf("- Capacidade máxima: %d motos\n", MAX_MOTORBIKES);
    pauseExecution();
}

/**
 * Esta função reinicia a base de dados, removendo todas as entradas.
 * Ela solicita confirmação ao usuário antes de prosseguir.
 * Se o usuário confirmar, a base de dados é reiniciada e uma mensagem de sucesso é exibida.
 * Se o usuário cancelar, uma mensagem de cancelamento é exibida.
 *
 * @param bd Ponteiro para a estrutura da base de dados.
 */
void restartDatabase(struct Database *bd)
{
    // Declaração da variável para armazenar a confirmação do usuário
    char confirmRestart;

    // Exibição do título da operação
    printf("=== Reiniciar Base de Dados ===\n\n");

    // Solicitação de confirmação ao usuário
    printf("Tem certeza que deseja reiniciar a base de dados? Isso excluirá todas as entradas. (s/n): ");

    // Leitura da confirmação do usuário
    scanf(" %c", &confirmRestart);

    // Consumo da nova linha após o caractere de entrada
    getchar();

    // Verificação da confirmação do usuário
    if (tolower(confirmRestart) == 's')
    {
        // Reinicialização da contagem de entradas da base de dados
        bd->totalCount = 0;

        // Exibição da mensagem de sucesso
        printf("\nBase de dados reiniciada com sucesso.\n");
    }
    else
    {
        // Exibição da mensagem de cancelamento
        printf("\nReiniciamento cancelado.\n");
    }

    // Pausa a execução do programa para permitir a visualização da mensagem
    pauseExecution();
}
