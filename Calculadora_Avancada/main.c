// Define que vamos usar constantes da 'math.h' (como M_PI)
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // Para as funções matemáticas (sqrt, sin, cos...)

// --- Constantes ---
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

// Nome do arquivo onde vamos salvar o histórico
#define NOME_ARQUIVO_HISTORICO "historico.csv"

// --- Structs ---

// "Molde" para uma Matriz 2x2
typedef struct {
    double elementos[2][2];
} Matriz2x2;

// "Molde" para uma operação 
typedef struct{
    char tipo[50];
    double n1, n2;
    double resultado;
    int id;
    Matriz2x2 resultadoMatriz; // Para guardar o resultado das matrizes
} Operacao;

// --- Variáveis Globais ---
#define MAX_HISTORICO 100
Operacao historico[MAX_HISTORICO]; // Array de "fichas" para o histórico
int numOperacoes = 0; // Contador de quantas operações fizemos

// --- Funções Auxiliares ---

// Função SUPER IMPORTANTE.
// Limpa a "sujeira" (tipo o ENTER) que o scanf deixa pra trás.
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
} 
    
// Função para salvar uma operação no nosso histórico
void adicionarAoHistorico(Operacao op) {
    if (numOperacoes < MAX_HISTORICO) {
        // Se tem espaço, só adiciona no final
        historico[numOperacoes] = op;
        numOperacoes++;
    } else {
        // Se o histórico está cheio, "empurra" todo mundo
        // (o item 0 some e o novo entra no final)
        printf("Historico cheio! A operacao antiga foi removida.\n");
        for (int i = 0; i < MAX_HISTORICO - 1; i++) {
            historico[i] = historico[i + 1];
        }
        historico[MAX_HISTORICO - 1] = op;
    }
}

// Função para salvar o histórico num arquivo .csv (tipo Excel)
void salvarHistoricoEmArquivo(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "w"); // "w" = write (escrever)
    if (f == NULL) {
        printf("Erro ao tentar salvar o historico em %s\n", nomeArquivo);
        return;
    }

    // Escreve o cabeçalho (a primeira linha do CSV)
    fprintf(f, "ID;Tipo;N1;N2;Resultado\n");

    // Passa por cada operação no histórico e escreve no arquivo
    for (int i = 0; i < numOperacoes; i++) {
        Operacao op = historico[i];
        // O CSV não salva as matrizes (ID 23 e 24), só os cálculos normais
        if (op.id < 23) { 
             fprintf(f, "%d;%s;%lf;%lf;%lf\n",
                op.id, op.tipo, op.n1, op.n2, op.resultado);
        }
    }

    fclose(f); // Fecha o arquivo (MUITO IMPORTANTE)
    printf("Historico salvo com sucesso em %s\n", nomeArquivo);
}

// Função para ler o histórico do arquivo .csv quando o programa começa
void carregarHistoricoDoArquivo(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r"); // "r" = read (ler)
    if (f == NULL) {
        // Se o arquivo não existe, tudo bem, só avisamos.
        printf("Arquivo de historico %s nao encontrado. Comecando com historico vazio.\n", nomeArquivo);
        return;
    }

    char linha[256];
    // Lê a primeira linha (o cabeçalho) e joga fora
    fgets(linha, sizeof(linha), f);

    // Agora lê o resto do arquivo, linha por linha
    while (numOperacoes < MAX_HISTORICO && // Não deixa estourar o histórico
           fscanf(f, "%d;%49[^;];%lf;%lf;%lf\n", // O formato que a gente espera
                  &historico[numOperacoes].id,
                  historico[numOperacoes].tipo,
                  &historico[numOperacoes].n1,
                  &historico[numOperacoes].n2,
                  &historico[numOperacoes].resultado) == 5) // Espera ler 5 "coisas"
    {
        // Se deu certo, aumenta o contador
        numOperacoes++;
    }

    fclose(f); // Fecha o arquivo
    printf("Historico carregado. %d operacoes recuperadas.\n", numOperacoes);
}

// Função para ler uma matriz 2x2
void lerMatriz2x2(Matriz2x2 *matriz, const char *nome) {
    int ler;
    printf("Digite os elementos da Matriz %s (2x2):\n", nome);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            // Loop do-while para garantir que o usuário digite um número
            do {
                printf("Elemento [%d][%d]: ", i + 1, j + 1);
                ler = scanf("%lf", &matriz->elementos[i][j]);
                if (ler != 1) { // Se o scanf falhou
                    printf("Erro! Isso nao e um numero.\n");
                    limparBufferEntrada(); // Limpa a sujeira (ex: 'abc')
                }
            } while (ler != 1);
        }
    }
}

// Funcao para exibir uma matriz 2x2
void exibirMatriz2x2(Matriz2x2 matriz) {
    printf("[ %.2lf  %.2lf ]\n", matriz.elementos[0][0], matriz.elementos[0][1]);
    printf("[ %.2lf  %.2lf ]\n", matriz.elementos[1][0], matriz.elementos[1][1]);
}

// --- Funções de Operação ---

void adicaoOperacao() {
    double operandos[2]; 
    Operacao op; // Cria uma "ficha" em branco
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                      Adicao\n");
    printf("--------------------------------------------------\n");

    // Loop para pedir os 2 números
    for (int i = 0; i < 2; i++) {
        do {
            printf("Digite o %s numero: \n", (i == 0) ? "primeiro" : "segundo");
            ler = scanf("%lf", &operandos[i]); 
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
    }
    
    // Coloca os números na "ficha"
    op.n1 = operandos[0]; 
    op.n2 = operandos[1];
    
    // Faz o cálculo
    op.resultado = op.n1 + op.n2;
    
    // Preenche o resto da "ficha"
    strcpy(op.tipo, "Adicao");
    op.id = 1;
    
    // Mostra o resultado e salva
    printf("\nResultado: %.2lf + %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER do último scanf
}

void subtracaoOperacao() {
    double operandos[2]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                     Subtracao\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 2; i++) {
        do {
            printf("Digite o %s numero: \n", (i == 0) ? "primeiro" : "segundo");
            ler = scanf("%lf", &operandos[i]); 
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
    }
    
    op.n1 = operandos[0]; 
    op.n2 = operandos[1];
    op.resultado = op.n1 - op.n2; // Cálculo
    
    strcpy(op.tipo, "Subtracao");
    op.id = 2;
    
    printf("\nResultado: %.2lf - %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void multiplicacaoOperacao() {
    double operandos[2]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                   Multiplicacao\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 2; i++) {
        do {
            printf("Digite o %s numero: \n", (i == 0) ? "primeiro" : "segundo");
            ler = scanf("%lf", &operandos[i]); 
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
    }
    
    op.n1 = operandos[0]; 
    op.n2 = operandos[1];
    op.resultado = op.n1 * op.n2; // Cálculo
    
    strcpy(op.tipo, "Multiplicacao");
    op.id = 3;
    
    printf("\nResultado: %.2lf * %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void divisaoOperacao() {
    double operandos[2]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                      Divisao\n");
    printf("--------------------------------------------------\n");
    
    // Pede o primeiro número
    do {
        printf("Digite o primeiro numero: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);

    // Pede o segundo número e valida (não pode ser 0)
    do {
        printf("Digite o segundo numero: \n");
        ler = scanf("%lf", &operandos[1]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        } else if (operandos[1] == 0.0) { // Validação de divisão por zero
            printf("Erro: Divisao por zero!\n");
            ler = 0; // Força o loop a rodar de novo
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = operandos[1];
    op.resultado = op.n1 / op.n2; // Cálculo
    
    strcpy(op.tipo, "Divisao");
    op.id = 4;
    
    printf("\nResultado: %.2lf / %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void raizquadradaOperacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                   Raiz Quadrada\n");
    printf("--------------------------------------------------\n");
    
    // Pede o número e valida (não pode ser negativo)
    do {
        printf("Digite o numero: \n");
        ler = scanf("%lf", &operandos[0]); 
        
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        // (BUG CORRIGIDO: era <= 0, agora é < 0. Raiz de 0 pode.)
        } else if (operandos[0] < 0.0) { 
            printf("Erro: Nao existe raiz real de numero negativo!\n");
            ler = 0; // Força o loop a rodar de novo
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = 0; // Não usa o n2
    op.resultado = sqrt(op.n1); // Cálculo
    
    strcpy(op.tipo, "Raiz Quadrada");
    op.id = 5;
    
    printf("Resultado: √%.2lf = %.2lf\n",op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void raizcubicaOperacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                    Raiz Cubica\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o numero: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = cbrt(op.n1); // Cálculo (pode número negativo)
    
    strcpy(op.tipo, "Raiz Cubica");
    op.id = 6;
    
    printf("Resultado: 3√%.2lf = %.2lf\n",op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}


void senoOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                        Seno\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o angulo em graus: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = sin(op.n1 * M_PI / 180); // Cálculo
    
    strcpy(op.tipo, "Seno");
    op.id = 7;
    
    printf("Resultado: sen(%.2lf°) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void cossenoOperacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                      Cosseno\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o angulo em graus: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = cos(op.n1 * M_PI / 180); // Cálculo
    
    strcpy(op.tipo, "Cosseno");
    op.id = 8;
    
    printf("Resultado: cos(%.2lf°) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void tangenteOperacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                     Tangente\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o angulo em graus: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        // Validação (tangente de 90, 270, etc. não existe)
        } else if (fmod(operandos[0], 180) == 90.0) {
            printf("Erro: Tangente indefinida para angulos de 90°, 270°, etc.\n");
            ler = 0; // Força o loop
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = tan(op.n1 * M_PI / 180); // Cálculo
    
    strcpy(op.tipo, "Tangente");
    op.id = 9;
    
    printf("Resultado: tan(%.2lf°) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void logbase10Operacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                  Logaritmo Base 10\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o logaritmo: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        // (BUG CORRIGIDO: log não pode ser de 0 ou negativo)
        } else if (operandos[0] <= 0.0) {
            printf("Erro: O logaritmando deve ser maior que zero.\n");
            ler = 0; // Força o loop
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = log10(op.n1); // Cálculo
    
    strcpy(op.tipo, "Logaritmo Base 10");
    op.id = 10;
    
    printf("Resultado: log10(%.2lf) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void lognaturalOperacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                  Logaritmo Natural\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o logaritmo: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        // (BUG CORRIGIDO: igual o log10)
        } else if (operandos[0] <= 0.0) {
            printf("Erro: O logaritmando deve ser maior que zero.\n");
            ler = 0; // Força o loop
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = log(op.n1); // Cálculo
    
    strcpy(op.tipo, "Logaritmo Natural");
    op.id = 11;
    
    printf("Resultado: ln(%.2lf) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void exponenciacaoOperacao () {
    double operandos[2]; 
    Operacao op; 
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                   Exponenciacao\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < 2; i++) {
        do {
            printf("Digite o %s numero: \n", (i == 0) ? "base" : "expoente");
            ler = scanf("%lf", &operandos[i]); 
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
    }
    
    op.n1 = operandos[0]; 
    op.n2 = operandos[1];
    op.resultado = pow(op.n1, op.n2); // Cálculo
    
    strcpy(op.tipo, "Exponenciacao");
    op.id = 12;
    
    printf("Resultado: %.2lf ^ %.2lf = %.2lf\n", op.n1, op.n2, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void exponencialOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                     Exponencial\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o numero (expoente e^x): \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);
    // (BUG CORRIGIDO: tirada a validação que proibia e^0)
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = exp(op.n1); // Cálculo
    
    strcpy(op.tipo, "Exponencial");
    op.id = 13;
    
    printf("Resultado: e^(%.2lf) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void calculoquadradoOperacao () {
    double operandos[1]; 
    Operacao op; 
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                  Calculo Quadrado\n");
    printf("--------------------------------------------------\n");

    do {
        printf("Digite o numero: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = op.n1; // Salva o n1 no n2 só pro histórico ficar bonito
    op.resultado = op.n1 * op.n1; // Cálculo
    
    strcpy(op.tipo, "Calculo Quadrado");
    op.id = 14;
    
    printf("\nResultado: %.2lf * %.2lf = %.2lf \n", op.n1, op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void arcosenoOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                     Arco Seno\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o valor entre -1 e 1: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        } else if (operandos[0] < -1.0 || operandos[0] > 1.0) {
            printf("Erro: O valor para o Arco Seno deve estar entre -1 e 1.\n");
            ler = 0; // Força o loop
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = asin(op.n1) * 180 / M_PI; // Cálculo
    
    strcpy(op.tipo, "Arco Seno");
    op.id = 15;
    
    printf("Resultado: asin(%.2lf) = %.2lf°\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void arcocossenoOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                    Arco Cosseno\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o valor entre -1 e 1: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        } else if (operandos[0] < -1.0 || operandos[0] > 1.0) {
            printf("Erro: O valor para o Arco Cosseno deve estar entre -1 e 1.\n");
            ler = 0; // Força o loop
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = acos(op.n1) * 180 / M_PI; // Cálculo
    
    strcpy(op.tipo, "Arco Cosseno");
    op.id = 16;
    
    printf("Resultado: acos(%.2lf) = %.2lf°\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void arcotanOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                  Arco Tangente\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o valor: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = atan(op.n1) * 180 / M_PI; // Cálculo
    
    strcpy(op.tipo, "Arco Tangente");
    op.id = 17;
    
    printf("Resultado: atan(%.2lf) = %.2lf°\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void porcentagemOperacao () {
    double operandos[2]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                   Porcentagem\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o Valor (ex: 150): \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);

    do {
        printf("Digite a Porcentagem (ex: 10 para 10%%): \n");
        ler = scanf("%lf", &operandos[1]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; // Valor
    op.n2 = operandos[1]; // %
    op.resultado = (op.n2 / 100.0) * op.n1; // Cálculo
    
    strcpy(op.tipo, "Porcentagem");
    op.id = 18;
    
    printf("Resultado: %.2lf%% de %.2lf = %.2lf\n", op.n2, op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void descontoOperacao () {
    double operandos[2]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                      Desconto\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o Valor do Produto: \n");
        ler = scanf("%lf", &operandos[1]); // Salva o produto em [1]
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);

    do {
        printf("Digite o Desconto (ex: 25 para 25%%): \n");
        ler = scanf("%lf", &operandos[0]); // Salva o % em [0]
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        } else if (operandos[0] < 0) {
            printf("Erro: O desconto nao pode ser negativo.\n");
            ler = 0;
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; // %
    op.n2 = operandos[1]; // Produto
    op.resultado = op.n2 - ((op.n1 * op.n2) / 100.0); // Cálculo
    
    strcpy(op.tipo, "Desconto");
    op.id = 19;
    
    printf("Resultado: Valor final com %.2lf%% de desconto = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void celparafahOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                Celsius para Fahrenheit\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o valor de Celsius: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = (op.n1 * 1.8) + 32; // Cálculo
    
    strcpy(op.tipo, "Celsius para Fahrenheit");
    op.id = 20;
    
    printf("Resultado: %.2lf°C = %.2lf°F\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void fahparacelOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                Fahrenheit para Celsius\n");
    printf("--------------------------------------------------\n");
    
    do {
        printf("Digite o valor de Fahrenheit: \n");
        ler = scanf("%lf", &operandos[0]); 
        if (ler != 1) {
            printf("Erro! Isso nao e um numero.\n");
            limparBufferEntrada();
        }
    } while (ler != 1);
    // (BUG CORRIGIDO: tirada a validação que proibia temp < 32°F)
    
    op.n1 = operandos[0]; 
    op.n2 = 0;
    op.resultado = (op.n1 - 32) * 5 / 9; // Cálculo
    
    strcpy(op.tipo, "Fahrenheit para Celsius");
    op.id = 21;
    
    printf("Resultado: %.2lf°F = %.2lf°C\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER
}

void mediaOperacao () {
    int N;
    int ler;
    double numero, soma = 0.0, media;
    Operacao op;

    printf("\n--------------------------------------------------\n");
    printf("                        Media\n");
    printf("--------------------------------------------------\n");

    // Pergunta QUANTOS números
    do {
        printf("Quantos numeros voce deseja para calcular a media? (maximo 100): \n");
        ler = scanf("%d", &N);
        if (ler != 1 || N <= 0 || N > 100) {
            printf("Erro! Digite um numero inteiro positivo (maximo 100).\n");
            limparBufferEntrada();
            ler = 0; 
        }
    } while (ler != 1 || N <= 0 || N > 100);
    limparBufferEntrada(); // Limpa o ENTER do scanf do 'N'
    
    // Pede CADA número
    for (int i = 0; i < N; i++) {
        do {
            printf("Digite o %d numero: \n", i + 1);
            ler = scanf("%lf", &numero);
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
        soma += numero; // Soma o número
    }
    
    if (N > 0) {
        media = soma / N;
    } else {
        media = 0.0;
    }

    op.n1 = (double)N; // Guarda N em n1
    op.n2 = soma; // Guarda a soma em n2
    op.resultado = media;
    
    strcpy(op.tipo, "Media");
    op.id = 22;
    
    printf("\nResultado: A media de %d numeros e %.2lf \n", N, op.resultado);
    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER do último scanf
}

void somaMatriz2x2Operacao() {
    Matriz2x2 matA, matB;
    Operacao op; // A matriz resultante vai DENTRO da "ficha" op

    printf("\n--------------------------------------------------\n");
    printf("                 Soma de Matriz 2x2\n");
    printf("--------------------------------------------------\n");

    lerMatriz2x2(&matA, "A"); // Usa a função auxiliar de ler matriz
    lerMatriz2x2(&matB, "B");

    // Faz o cálculo e salva direto na 'op.resultadoMatriz'
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            op.resultadoMatriz.elementos[i][j] = matA.elementos[i][j] + matB.elementos[i][j];
        }
    }

    // Preenche o resto da "ficha"
    strcpy(op.tipo, "Soma de Matriz 2x2");
    op.id = 23;
    op.n1 = 0.0; // Não usados
    op.n2 = 0.0;
    op.resultado = 0.0; // Não usado

    printf("\nMatriz Resultante (A + B):\n");
    exibirMatriz2x2(op.resultadoMatriz); // Mostra a matriz
    printf("\n");

    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER do último scanf da matriz
}

void multiplicacaoMatriz2x2Operacao() {
    Matriz2x2 matA, matB;
    Operacao op;

    printf("\n--------------------------------------------------\n");
    printf("            Multiplicacao de Matriz 2x2\n");
    printf("--------------------------------------------------\n");

    lerMatriz2x2(&matA, "A");
    lerMatriz2x2(&matB, "B");

    // Zera a matriz de resultado antes de calcular
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            op.resultadoMatriz.elementos[i][j] = 0.0;
        }
    }

    // Cálculo da multiplicação (linha de A * coluna de B)
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                op.resultadoMatriz.elementos[i][j] += matA.elementos[i][k] * matB.elementos[k][j];
            }
        }
    }

    strcpy(op.tipo, "Multiplicacao de Matriz 2x2");
    op.id = 24;
    op.n1 = 0.0;
    op.n2 = 0.0;
    op.resultado = 0.0;
    // op.resultadoMatriz já foi preenchida

    printf("\nMatriz Resultante (A * B):\n");
    exibirMatriz2x2(op.resultadoMatriz);
    printf("\n");

    adicionarAoHistorico(op);
    limparBufferEntrada(); // Limpa o ENTER do último scanf da matriz
}

// Função para mostrar o histórico
void exibirOperacao() {
    if (numOperacoes == 0) {
        printf("Nao ha operacoes feitas ainda.\n");
        return;
    }

    printf("--------------------------------------------------\n");
    printf("               Historico das Operacoes\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < numOperacoes; i++) {
        Operacao op = historico[i];
        printf("%03d) Tipo: %-25s | ", i + 1, op.tipo);

        // (BUG CORRIGIDO: Adição estava com %2.lf, mudei para %.2lf)
        if (op.id == 1) {
            printf("Resultado: %.2lf + %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
        } else if (op.id == 2) {
            printf("Resultado: %.2lf - %.2lf = %.2lf\n", op.n1, op.n2, op.resultado);
        } else if (op.id == 3) {
            printf("Resultado: %.2lf * %.2lf = %.2lf\n", op.n1, op.n2, op.resultado);
        } else if (op.id == 4) {
            printf("Resultado: %.2lf / %.2lf = %.2lf\n", op.n1, op.n2, op.resultado);
        } else if (op.id == 5) {
            printf("Resultado: √%.2lf = %.2lf\n",op.n1, op.resultado);
        } else if (op.id == 6) {
            printf("Resultado: 3√%.2lf = %.2lf\n",op.n1, op.resultado);
        } else if (op.id == 7) {
            printf("Resultado: sen(%.2lf°) = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 8) {
            printf("Resultado: cos(%.2lf°) = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 9) {
            printf("Resultado: tan(%.2lf°) = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 10) {
            printf("Resultado: log10(%.2lf) = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 11) {
            printf("Resultado: ln(%.2lf) = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 12) {
            printf("Resultado: %.2lf ^ %.2lf = %.2lf\n", op.n1, op.n2, op.resultado);
        } else if (op.id == 13) {
            printf("Resultado: e^(%.2lf) = %.2lf\n", op.n1, op.resultado);
        } else if  (op.id == 14) {
            printf("Resultado: %.2lf * %.2lf = %.2lf\n", op.n1, op.n1, op.resultado);
        } else if (op.id == 15) {
            printf("Resultado: asin(%.2lf) = %.2lf°\n", op.n1, op.resultado);
        } else if (op.id == 16) {
            printf("Resultado: acos(%.2lf) = %.2lf°\n", op.n1, op.resultado);
        } else if (op.id == 17) {
            printf("Resultado: atan(%.2lf) = %.2lf°\n", op.n1, op.resultado);
        } else if (op.id == 18) {
            printf("Resultado: %.2lf%% de %.2lf = %.2lf\n", op.n2, op.n1, op.resultado);
        } else if (op.id == 19) {   
            printf("Resultado: Valor final com %.2lf%% desc. = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 20) {
            printf("Resultado: %.2lf°C = %.2lf°F\n", op.n1, op.resultado);
        } else if (op.id == 21) {
            printf("Resultado: %.2lf°F = %.2lf°C\n", op.n1, op.resultado);
        } else if (op.id == 22) {
            printf("Resultado: A media de %d numeros e %.2lf\n", (int)op.n1, op.resultado);
        // (Lógica do Código B para mostrar a matriz)
        } else if (op.id == 23) { 
            printf("Resultado da Soma:\n");
            // Adiciona espaços para alinhar a matriz
            printf("                                     [ %.2lf  %.2lf ]\n", op.resultadoMatriz.elementos[0][0], op.resultadoMatriz.elementos[0][1]);
            printf("                                     [ %.2lf  %.2lf ]\n", op.resultadoMatriz.elementos[1][0], op.resultadoMatriz.elementos[1][1]);
        } else if (op.id == 24) {
            printf("Resultado da Multiplicacao:\n");
            printf("                                     [ %.2lf  %.2lf ]\n", op.resultadoMatriz.elementos[0][0], op.resultadoMatriz.elementos[0][1]);
            printf("                                     [ %.2lf  %.2lf ]\n", op.resultadoMatriz.elementos[1][0], op.resultadoMatriz.elementos[1][1]);
        }
    }
}   

// --- Função Principal (main) ---
int main()
{
    int opcao;
    int continuar;

    //Carrega o histórico do arquivo
    carregarHistoricoDoArquivo(NOME_ARQUIVO_HISTORICO);

    do {
        printf("--------------------------------------------------\n");
        printf("             CALCULADORA CIENTIFICA\n");
        printf("--------------------------------------------------\n");
        printf("\nOpcoes: \n");
        printf("\n--------------------------------------------------\n");
        printf("               Operacoes Basicas\n");
        printf("--------------------------------------------------\n");
        printf("1 - Adicao\n");
        printf("2 - Subtracao\n");
        printf("3 - Multiplicacao\n");
        printf("4 - Divisao\n");
        printf("\n--------------------------------------------------\n");
        printf("               Operacoes Adicionais\n");
        printf("--------------------------------------------------\n");
        printf("5 - Raiz Quadrada\n");
        printf("6 - Raiz Cubica\n");
        printf("7 - Seno\n");
        printf("8 - Cosseno\n");
        printf("9 - Tangente\n");
        printf("10 - Logaritmo Base 10\n");
        printf("11 - Logaritmo Natural\n");
        printf("12 - Exponenciacao\n");
        printf("13 - Exponencial\n");
        printf("14 - Calculo Quadrado\n");
        printf("15 - Arco Seno\n");
        printf("16 - Arco Cosseno\n");
        printf("17 - Arco Tangente\n");
        printf("18 - Porcentagem\n");
        printf("19 - Desconto\n");
        printf("20 - Celsius para Fahrenheit\n");
        printf("21 - Fahrenheit para Celsius\n");
        printf("22 - Media\n");
        printf("\n--------------------------------------------------\n");
        printf("                       Matriz\n");
        printf("--------------------------------------------------\n");
        printf("23 - Soma de Matriz 2x2\n");
        printf("24 - Multiplicacao de Matriz 2x2\n");
        printf("\n--------------------------------------------------\n");
        printf("                       Historico\n");
        printf("--------------------------------------------------\n");
        printf("25 - Historico\n");
        printf("\n--------------------------------------------------\n");
        printf("               SAIR DA CALCULADORA\n");
        printf("--------------------------------------------------\n");
        printf("0 - Para sair (e Salvar Historico)\n"); // (Texto atualizado)
        printf("\n--------------------------------------------------\n");
        printf("Digite a opcao: \n");
        
        // Validação da opção do menu
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida! Digite um numero.\n");
            limparBufferEntrada();
            continuar = 1; // Força o loop a rodar de novo
            continue; // Pula o resto do switch
        }
        limparBufferEntrada(); // Limpa o ENTER

        switch (opcao) {
            case 1: adicaoOperacao(); break;
            case 2: subtracaoOperacao(); break;
            case 3: multiplicacaoOperacao(); break;
            case 4: divisaoOperacao(); break;
            case 5: raizquadradaOperacao(); break;
            case 6: raizcubicaOperacao(); break;
            case 7: senoOperacao(); break;
            case 8: cossenoOperacao(); break;
            case 9: tangenteOperacao(); break;
            case 10: logbase10Operacao(); break;
            case 11: lognaturalOperacao(); break;
            case 12: exponenciacaoOperacao(); break;
            case 13: exponencialOperacao(); break;
            case 14: calculoquadradoOperacao(); break;
            case 15: arcosenoOperacao(); break;
            case 16: arcocossenoOperacao(); break;
            case 17: arcotanOperacao(); break;
            case 18: porcentagemOperacao(); break;
            case 19: descontoOperacao(); break;
            case 20: celparafahOperacao(); break;
            case 21: fahparacelOperacao(); break;
            case 22: mediaOperacao(); break;
            case 23: somaMatriz2x2Operacao(); break;
            case 24: multiplicacaoMatriz2x2Operacao(); break;
            case 25: exibirOperacao(); break;
            case 0:
                printf("\n--------------------------------------------------\n");
                printf("           Saindo da calculadora! Ate mais.\n");
                //  Salva o histórico antes de sair
                salvarHistoricoEmArquivo(NOME_ARQUIVO_HISTORICO);
                printf("--------------------------------------------------\n");
                return 0; // Sai do programa
            default:
                printf("Opcao invalida!\n");
                break;
        }

        printf("\n--------------------------------------------------\n");
        printf("Deseja fazer outro calculo? (1 para Sim/ 0 para Nao): ");
        
        if (scanf("%d", &continuar) != 1) {
             continuar = 0; // Se digitar 'a', sai por segurança
        }
        
        // (BUG CRÍTICO CORRIGIDO: Este é o 'limpar' que faltava)
        // Sem ele, o scanf("%d", &opcao) lá de cima pega o ENTER
        // e entra em loop infinito.
        limparBufferEntrada(); 

    } while (continuar == 1);

    // Salva também se o usuário digitar '0' aqui
    printf("Saindo...\n");
    salvarHistoricoEmArquivo(NOME_ARQUIVO_HISTORICO);
    return 0; 
}
