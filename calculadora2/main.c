// Define que vamos usar constantes da 'math.h' (como M_PI)
#define _USE_MATH_DEFINES 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // Para as funções matemáticas (sqrt, sin, cos...)

// --- Constantes ---

// Define o PI se a biblioteca 'math.h' não definir
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
// Define o número de Euler (E) se não estiver definido
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

// Define o tamanho máximo do nosso histórico
#define MAX_HISTORICO 100
// Nome do arquivo onde vamos salvar o histórico (Bônus)
#define NOME_ARQUIVO_HISTORICO "historico.csv"

// --- Estruturas (Structs) ---

// Aqui a gente define o "molde" para guardar uma operação
// É como uma ficha para cada cálculo que a gente faz
typedef struct {
    char tipo[50];    // O nome da operação (ex: "Adicao")
    double n1, n2;    // Os números que o usuário digitou
    double resultado; // O resultado do cálculo
    int id;           // Um número pra gente saber qual é a operação (ex: 1 = Adição)
} Operacao;

// --- Variáveis Globais ---

// Criamos um "array" (um monte de) de Operacoes para ser o histórico
Operacao historico[MAX_HISTORICO];
// Um contador para saber quantas operações já fizemos e guardamos
int numOperacoes = 0;

// =================================================================
// --- Funções Auxiliares (Utilitários) ---
// =================================================================

/**
 * Função SUPER IMPORTANTE.
 * Ela limpa o "buffer" (a sujeira) que o scanf deixa pra trás (tipo o ENTER).
 * Isso evita que o programa entre em loop infinito ou pule perguntas.
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Esta função serve para ler um número do tipo "double" (com vírgula)
 * de um jeito seguro. Ela fica repetindo até o usuário digitar um número certo.
 * 'prompt' é a mensagem que aparece (tipo "Digite um número:")
 * 'numero' é onde vamos guardar o número que o usuário digitou (por isso o *)
 */
void lerDouble(const char* prompt, double* numero) {
    int ler; // Variável pra checar se o scanf deu certo
    do {
        printf("%s", prompt); // Mostra a mensagem
        ler = scanf("%lf", numero); // Tenta ler o número
        
        if (ler != 1) { // Se o scanf não retornou 1 (ou seja, deu erro)
            printf("Erro! Isso nao e um numero. Tente novamente.\n");
            limparBufferEntrada(); // Limpa a sujeira (ex: o usuário digitou 'abc')
        }
    } while (ler != 1); // Fica no loop enquanto o usuário não digitar certo
    
    // Depois que digita certo, ainda tem o ENTER que ele apertou
    limparBufferEntrada(); // Limpa esse ENTER
}

/**
 * Função para ler uma matriz 2x2
 * 'matriz' é o array 2x2 que vamos preencher
 */
void lerMatriz2x2(double matriz[2][2]) {
    printf("Digite os elementos da matriz 2x2:\n");
    for (int i = 0; i < 2; i++) { // Loop da linha
        for (int j = 0; j < 2; j++) { // Loop da coluna
            char prompt[50];
            // sprintf junta texto para formar a mensagem "Elemento [0][0]: "
            sprintf(prompt, "Elemento [%d][%d]: ", i, j);
            // Usa nossa função segura de ler número
            lerDouble(prompt, &matriz[i][j]);
        }
    }
}

/**
 * Função para mostrar a matriz 2x2 bonitinha
 */
void imprimirMatriz2x2(double matriz[2][2]) {
    for (int i = 0; i < 2; i++) {
        printf("| %.2lf  %.2lf |\n", matriz[i][0], matriz[i][1]);
    }
}


// =================================================================
// --- Funções de Histórico e Arquivo (Bônus) ---
// =================================================================

/**
 * Função para salvar uma operação no nosso histórico (o array 'historico')
 * 'op' é a ficha da operação que a gente quer guardar
 */
void adicionarAoHistorico(Operacao op) {
    if (numOperacoes < MAX_HISTORICO) {
        // Se tem espaço, só adiciona no final
        historico[numOperacoes] = op;
        numOperacoes++; // Aumenta o contador
    } else {
        // Se o histórico está cheio (100 operações)
        // printf("Historico cheio! Removendo a operacao mais antiga.\n"); // Pode tirar o aviso se não quiser
        
        // "Empurra" todo mundo pra esquerda (o item 0 some)
        for (int i = 0; i < MAX_HISTORICO - 1; i++) {
            historico[i] = historico[i + 1];
        }
        // Coloca a operação nova no último lugar
        historico[MAX_HISTORICO - 1] = op;
    }
}

/**
 * (BÔNUS) Função para salvar o histórico num arquivo .csv (tipo Excel)
 * 'nomeArquivo' é o nome do arquivo que vamos criar/sobrescrever
 */
void salvarHistoricoEmArquivo(const char* nomeArquivo) {
    // Tenta abrir o arquivo para escrever ("w" = write)
    FILE* f = fopen(nomeArquivo, "w");
    if (f == NULL) {
        // Se deu erro (ex: sem permissão)
        printf("Erro ao tentar salvar o historico em %s\n", nomeArquivo);
        return; // Sai da função
    }

    // Escreve o cabeçalho (a primeira linha do CSV)
    fprintf(f, "ID;Tipo;N1;N2;Resultado\n");

    // Passa por cada operação no histórico e escreve no arquivo
    for (int i = 0; i < numOperacoes; i++) {
        Operacao op = historico[i];
        fprintf(f, "%d;%s;%lf;%lf;%lf\n",
                op.id, op.tipo, op.n1, op.n2, op.resultado);
    }

    fclose(f); // Fecha o arquivo (MUITO IMPORTANTE)
    printf("Historico salvo com sucesso em %s\n", nomeArquivo);
}

/**
 * (BÔNUS) Função para ler o histórico do arquivo .csv quando o programa começa
 */
void carregarHistoricoDoArquivo(const char* nomeArquivo) {
    // Tenta abrir o arquivo para ler ("r" = read)
    FILE* f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        // Se o arquivo não existe, tudo bem, só avisamos.
        printf("Arquivo de historico %s nao encontrado. Comecando com historico vazio.\n", nomeArquivo);
        return; // Sai da função
    }

    char linha[256];
    // Lê a primeira linha (o cabeçalho) e joga fora
    fgets(linha, sizeof(linha), f);

    // Agora lê o resto do arquivo, linha por linha
    // O fscanf é chatinho, ele tenta ler os dados separados por ";"
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

// =================================================================
// --- Funções de CÁLCULO (A matemática pura) ---
// =================================================================
//
// Aqui é onde a mágica acontece.
// Essas funções SÓ fazem o cálculo, elas não falam com o usuário.
// Isso é bom pra organizar o código (requisito do professor).
//

// Soma
double calculaAdicao(double n1, double n2) { return n1 + n2; }

// Subtração
double calculaSubtracao(double n1, double n2) { return n1 - n2; }

// Multiplicação
double calculaMultiplicacao(double n1, double n2) { return n1 * n2; }

// Divisão (a gente já verificou se n2 é zero LÁ NA FUNÇÃO de operação)
double calculaDivisao(double n1, double n2) { return n1 / n2; }

// Raiz Quadrada
double calculaRaizQuadrada(double n1) { return sqrt(n1); }

// Raiz Cúbica
double calculaRaizCubica(double n1) { return cbrt(n1); }

// Seno (converte o ângulo de graus para radianos antes de calcular)
double calculaSeno(double anguloGraus) { return sin(anguloGraus * M_PI / 180.0); }

// Cosseno (mesma coisa, converte pra radianos)
double calculaCosseno(double anguloGraus) { return cos(anguloGraus * M_PI / 180.0); }

// Tangente
double calculaTangente(double anguloGraus) { return tan(anguloGraus * M_PI / 180.0); }

// Log na base 10
double calculaLog10(double n1) { return log10(n1); }

// Log natural (na base 'e')
double calculaLogNatural(double n1) { return log(n1); }

// Potência (base elevado ao expoente)
double calculaExponenciacao(double base, double expoente) { return pow(base, expoente); }

// Exponencial ('e' elevado ao número)
double calculaExponencial(double n1) { return exp(n1); }

// Número ao quadrado
double calculaQuadrado(double n1) { return n1 * n1; }

// Arco Seno (inverso do seno). Retorna em graus.
double calculaArcoSeno(double n1) { return asin(n1) * 180.0 / M_PI; }

// Arco Cosseno (inverso do cosseno). Retorna em graus.
double calculaArcoCosseno(double n1) { return acos(n1) * 180.0 / M_PI; }

// Arco Tangente (inverso da tangente). Retorna em graus.
double calculaArcoTangente(double n1) { return atan(n1) * 180.0 / M_PI; }

// Porcentagem (quanto é 'percentual'% de 'valor')
double calculaPorcentagem(double valor, double percentual) { return (percentual / 100.0) * valor; }

// Desconto (calcula o valor do desconto e tira do preço original)
double calculaDesconto(double valorProduto, double percentualDesconto) {
    double valorDesconto = (percentualDesconto / 100.0) * valorProduto;
    return valorProduto - valorDesconto;
}

// Celsius para Fahrenheit
double calculaCelsiusParaFah(double celsius) { return (celsius * 1.8) + 32; }

// Fahrenheit para Celsius
double calculaFahParaCelsius(double fah) { return (fah - 32) * 5.0 / 9.0; }

// Média (a gente passa a soma total e quantos números são)
double calculaMedia(double somaTotal, int N) {
    if (N <= 0) return 0.0; // Evita divisão por zero se N for 0
    return somaTotal / (double)N;
}

/**
 * (Matriz) Soma de matrizes 2x2
 * R = A + B
 */
void somarMatrizes2x2(double A[2][2], double B[2][2], double R[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            R[i][j] = A[i][j] + B[i][j];
        }
    }
}

/**
 * (Matriz) Multiplicação de matrizes 2x2 (essa é mais chatinha)
 * R = A * B
 */
void multiplicarMatrizes2x2(double A[2][2], double B[2][2], double R[2][2]) {
    // Pega Linha de A e Coluna de B
    R[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0]; // Linha 0, Coluna 0
    R[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1]; // Linha 0, Coluna 1
    R[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0]; // Linha 1, Coluna 0
    R[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1]; // Linha 1, Coluna 1
}


// =================================================================
// --- Funções de OPERAÇÃO (Interface com o Usuário) ---
// =================================================================
//
// Estas funções é que FALAM com o usuário.
// O trabalho delas é:
// 1. Mostrar o título (ex: "--- Adição ---")
// 2. Pedir os números (usando nossa função 'lerDouble')
// 3. Fazer validações (ex: não dividir por zero)
// 4. Chamar a função de CÁLCULO (ex: 'calculaAdicao')
// 5. Salvar o resultado na ficha 'Operacao' e mandar pro histórico
// 6. Mostrar o resultado pro usuário
//

void adicaoOperacao() {
    Operacao op; // Cria uma "ficha" de operação em branco
    printf("\n--------------------------------------------------\n");
    printf("                      Adicao\n");
    printf("--------------------------------------------------\n");

    // Pede os números e guarda direto na "ficha"
    lerDouble("Digite o primeiro numero: \n", &op.n1);
    lerDouble("Digite o segundo numero: \n", &op.n2);

    // Chama a função de cálculo e guarda o resultado
    op.resultado = calculaAdicao(op.n1, op.n2);

    // Preenche o resto da "ficha"
    strcpy(op.tipo, "Adicao");
    op.id = 1;
    
    // Mostra o resultado e salva no histórico
    printf("\nResultado: %.2lf + %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    adicionarAoHistorico(op);
}

void subtracaoOperacao() {
    Operacao op;
    printf("\n--------------------------------------------------\n");
    printf("                     Subtracao\n");
    printf("--------------------------------------------------\n");

    lerDouble("Digite o primeiro numero: \n", &op.n1);
    lerDouble("Digite o segundo numero: \n", &op.n2);

    op.resultado = calculaSubtracao(op.n1, op.n2);

    strcpy(op.tipo, "Subtracao");
    op.id = 2;
    printf("\nResultado: %.2lf - %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    adicionarAoHistorico(op);
}

void multiplicacaoOperacao() {
    Operacao op;
    printf("\n--------------------------------------------------\n");
    printf("                   Multiplicacao\n");
    printf("--------------------------------------------------\n");

    lerDouble("Digite o primeiro numero: \n", &op.n1);
    lerDouble("Digite o segundo numero: \n", &op.n2);

    op.resultado = calculaMultiplicacao(op.n1, op.n2);

    strcpy(op.tipo, "Multiplicacao");
    op.id = 3;
    printf("\nResultado: %.2lf * %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    adicionarAoHistorico(op);
}

void divisaoOperacao() {
    Operacao op;
    printf("\n--------------------------------------------------\n");
    printf("                      Divisao\n");
    printf("--------------------------------------------------\n");

    lerDouble("Digite o primeiro numero (dividendo): \n", &op.n1);
    lerDouble("Digite o segundo numero (divisor): \n", &op.n2);

    // Validação de divisão por zero!
    while (op.n2 == 0.0) {
        printf("Erro: Divisao por zero!\n");
        lerDouble("Digite o segundo numero (divisor) novamente (diferente de zero): \n", &op.n2);
    }

    op.resultado = calculaDivisao(op.n1, op.n2);

    strcpy(op.tipo, "Divisao");
    op.id = 4;
    printf("\nResultado: %.2lf / %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    adicionarAoHistorico(op);
}

void raizquadradaOperacao() {
    Operacao op;
    op.n2 = 0; // Essa operação só usa n1, então zeramos n2
    printf("\n--------------------------------------------------\n");
    printf("                   Raiz Quadrada\n");
    printf("--------------------------------------------------\n");

    lerDouble("Digite o numero: \n", &op.n1);

    // Validação (não pode raiz de número negativo)
    // (BUG CORRIGIDO: era <= 0, agora é < 0. Raiz de 0 pode.)
    while (op.n1 < 0.0) {
        printf("Erro: Nao existe raiz quadrada real de numero negativo!\n");
        lerDouble("Digite o numero novamente (maior ou igual a 0): \n", &op.n1);
    }

    op.resultado = calculaRaizQuadrada(op.n1);

    strcpy(op.tipo, "Raiz Quadrada");
    op.id = 5;
    printf("Resultado: √%.2lf = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void raizcubicaOperacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                    Raiz Cubica\n");
    printf("--------------------------------------------------\n");

    lerDouble("Digite o numero: \n", &op.n1);

    op.resultado = calculaRaizCubica(op.n1); // Raiz cúbica pode de número negativo

    strcpy(op.tipo, "Raiz Cubica");
    op.id = 6;
    printf("Resultado: 3√%.2lf = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}


void senoOperacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                        Seno\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o angulo em graus: \n", &op.n1);

    op.resultado = calculaSeno(op.n1);

    strcpy(op.tipo, "Seno");
    op.id = 7;
    printf("Resultado: sen(%.2lf°) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void cossenoOperacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                      Cosseno\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o angulo em graus: \n", &op.n1);

    op.resultado = calculaCosseno(op.n1);

    strcpy(op.tipo, "Cosseno");
    op.id = 8;
    printf("Resultado: cos(%.2lf°) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void tangenteOperacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                     Tangente\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o angulo em graus: \n", &op.n1);

    // Validação (tangente de 90, 270, etc. não existe / é infinito)
    // fmod é o "resto" da divisão para números com vírgula
    while (fmod(op.n1, 180) == 90.0) { 
         printf("Erro: Tangente indefinida para angulos de 90°, 270°, etc.\n");
         lerDouble("Digite outro angulo em graus: \n", &op.n1);
    }

    op.resultado = calculaTangente(op.n1);

    strcpy(op.tipo, "Tangente");
    op.id = 9;
    printf("Resultado: tan(%.2lf°) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void logbase10Operacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                  Logaritmo Base 10\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o logaritmando (numero > 0): \n", &op.n1);

    // Validação (log não pode ser de 0 ou negativo)
    while (op.n1 <= 0.0) {
        printf("Erro: O logaritmando deve ser maior que zero.\n");
        lerDouble("Digite o numero novamente (maior que 0): \n", &op.n1);
    }

    op.resultado = calculaLog10(op.n1);

    strcpy(op.tipo, "Logaritmo Base 10");
    op.id = 10;
    printf("Resultado: log10(%.2lf) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void lognaturalOperacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                  Logaritmo Natural\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o logaritmando (numero > 0): \n", &op.n1);

    // Validação (igual o log10)
    while (op.n1 <= 0.0) {
        printf("Erro: O logaritmando deve ser maior que zero.\n");
        lerDouble("Digite o numero novamente (maior que 0): \n", &op.n1);
    }

    op.resultado = calculaLogNatural(op.n1);

    strcpy(op.tipo, "Logaritmo Natural");
    op.id = 11;
    printf("Resultado: ln(%.2lf) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void exponenciacaoOperacao() {
    Operacao op;
    printf("\n--------------------------------------------------\n");
    printf("                   Exponenciacao\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o numero (base): \n", &op.n1);
    lerDouble("Digite o numero (expoente): \n", &op.n2);

    op.resultado = calculaExponenciacao(op.n1, op.n2);

    strcpy(op.tipo, "Exponenciacao");
    op.id = 12;
    printf("Resultado: %.2lf ^ %.2lf = %.2lf\n", op.n1, op.n2, op.resultado);
    adicionarAoHistorico(op);
}

void exponencialOperacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                     Exponencial\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o expoente (e^x): \n", &op.n1);

    // (BUG CORRIGIDO: tirei a validação que proibia e^0, porque e^0 = 1 e é válido)
    op.resultado = calculaExponencial(op.n1);

    strcpy(op.tipo, "Exponencial");
    op.id = 13;
    printf("Resultado: e^(%.2lf) = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void calculoquadradoOperacao() {
    Operacao op;
    op.n2 = 0; // Só usa n1
    printf("\n--------------------------------------------------\n");
    printf("                  Calculo Quadrado\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o numero: \n", &op.n1);
    op.n2 = op.n1; // Salva o n1 no n2 só pro histórico ficar bonito (n1 * n1)

    op.resultado = calculaQuadrado(op.n1);

    strcpy(op.tipo, "Calculo Quadrado");
    op.id = 14;
    printf("\nResultado: %.2lf * %.2lf = %.2lf \n", op.n1, op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void arcosenoOperacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                     Arco Seno\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o valor (entre -1 e 1): \n", &op.n1);

    // Validação (só existe arco seno de -1 até 1)
    while (op.n1 < -1.0 || op.n1 > 1.0) {
        printf("Erro: O valor para Arco Seno deve estar entre -1 e 1.\n");
        lerDouble("Digite o valor novamente: \n", &op.n1);
    }

    op.resultado = calculaArcoSeno(op.n1);

    strcpy(op.tipo, "Arco Seno");
    op.id = 15;
    printf("Resultado: asin(%.2lf) = %.2lf°\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void arcocossenoOperacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                    Arco Cosseno\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o valor (entre -1 e 1): \n", &op.n1);

    // Validação (igual arco seno)
    while (op.n1 < -1.0 || op.n1 > 1.0) {
        printf("Erro: O valor para Arco Cosseno deve estar entre -1 e 1.\n");
        lerDouble("Digite o valor novamente: \n", &op.n1);
    }

    op.resultado = calculaArcoCosseno(op.n1);

    strcpy(op.tipo, "Arco Cosseno");
    op.id = 16;
    printf("Resultado: acos(%.2lf) = %.2lf°\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void arcotanOperacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                  Arco Tangente\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o valor: \n", &op.n1); // Arco tangente aceita qualquer número

    op.resultado = calculaArcoTangente(op.n1);

    strcpy(op.tipo, "Arco Tangente");
    op.id = 17;
    printf("Resultado: atan(%.2lf) = %.2lf°\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void porcentagemOperacao() {
    Operacao op;
    printf("\n--------------------------------------------------\n");
    printf("                   Porcentagem\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o valor (ex: 150): \n", &op.n1);
    lerDouble("Digite a porcentagem (ex: 10 para 10%%): \n", &op.n2);

    op.resultado = calculaPorcentagem(op.n1, op.n2);

    strcpy(op.tipo, "Porcentagem");
    op.id = 18;
    // Inverti a ordem no printf pra ficar mais natural
    printf("Resultado: %.2lf%% de %.2lf = %.2lf\n", op.n2, op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void descontoOperacao() {
    Operacao op;
    printf("\n--------------------------------------------------\n");
    printf("                      Desconto\n");
    printf("--------------------------------------------------\n");
    // Pedi o produto primeiro, e guardei em n2
    lerDouble("Digite o Valor do Produto: \n", &op.n2); 
    // Pedi o desconto e guardei em n1
    lerDouble("Digite o Desconto (ex: 25 para 25%%): \n", &op.n1); 

    while (op.n1 < 0.0) { // Não faz sentido desconto negativo
        printf("Erro: O desconto nao pode ser negativo.\n");
        lerDouble("Digite o desconto novamente: \n", &op.n1);
    }

    op.resultado = calculaDesconto(op.n2, op.n1); // (produto, desconto)

    strcpy(op.tipo, "Desconto");
    op.id = 19;
    printf("Resultado: Valor final com %.2lf%% de desconto = %.2lf\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void celparafahOperacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                Celsius para Fahrenheit\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o valor em Celsius: \n", &op.n1);

    op.resultado = calculaCelsiusParaFah(op.n1);

    strcpy(op.tipo, "Celsius para Fahrenheit");
    op.id = 20;
    printf("Resultado: %.2lf°C = %.2lf°F\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void fahparacelOperacao() {
    Operacao op;
    op.n2 = 0;
    printf("\n--------------------------------------------------\n");
    printf("                Fahrenheit para Celsius\n");
    printf("--------------------------------------------------\n");
    lerDouble("Digite o valor de Fahrenheit: \n", &op.n1);

    // (BUG CORRIGIDO: tirei a validação que proibia temp < 32°F)
    op.resultado = calculaFahParaCelsius(op.n1);

    strcpy(op.tipo, "Fahrenheit para Celsius");
    op.id = 21;
    printf("Resultado: %.2lf°F = %.2lf°C\n", op.n1, op.resultado);
    adicionarAoHistorico(op);
}

void mediaOperacao() {
    Operacao op;
    int N; // Quantidade de números que o usuário quer
    int ler;
    double numero, soma = 0.0;

    printf("\n--------------------------------------------------\n");
    printf("                        Media\n");
    printf("--------------------------------------------------\n");

    // Loop para perguntar QUANTOS números
    do {
        printf("Quantos numeros voce deseja para calcular a media? (maximo 100): \n");
        ler = scanf("%d", &N);
        if (ler != 1 || N <= 0 || N > 100) {
            printf("Erro! Digite um numero inteiro positivo (maximo 100).\n");
            limparBufferEntrada();
            ler = 0;
        }
    } while (ler != 1 || N <= 0 || N > 100);
    limparBufferEntrada(); // Limpa o buffer após o scanf de N

    // Loop para pedir CADA número (usando um array "virtual")
    for (int i = 0; i < N; i++) {
        char prompt[50];
        sprintf(prompt, "Digite o %dº numero: \n", i + 1);
        lerDouble(prompt, &numero); // Usa o helper lerDouble
        soma += numero; // Vai somando tudo
    }

    op.resultado = calculaMedia(soma, N);
    op.n1 = (double)N; // Guarda quantos números foram em n1
    op.n2 = soma;       // Guarda a soma total em n2 (pro histórico)

    strcpy(op.tipo, "Media");
    op.id = 22;
    printf("\nResultado: A media de %d numeros (soma=%.2lf) e %.2lf \n", N, soma, op.resultado);
    adicionarAoHistorico(op);
}

void somaMatriz2x2Operacao() {
    // Nota: Esta operação não será salva "inteira" no histórico da struct 'Operacao'
    // pois a struct não foi projetada para armazenar matrizes.
    printf("\n--------------------------------------------------\n");
    printf("                 Soma de Matrizes 2x2\n");
    printf("--------------------------------------------------\n");

    double A[2][2], B[2][2], R[2][2]; // Nossas 3 matrizes

    printf("--- Matriz A ---\n");
    lerMatriz2x2(A); // Usa a função auxiliar pra ler A
    printf("\n--- Matriz B ---\n");
    lerMatriz2x2(B); // Usa a função auxiliar pra ler B

    somarMatrizes2x2(A, B, R); // Chama o cálculo

    printf("\n--- Resultado (A + B) ---\n");
    imprimirMatriz2x2(R); // Mostra o resultado

    // Adicionando ao histórico (de forma simplificada, só pra constar)
    Operacao op;
    op.id = 23;
    strcpy(op.tipo, "Soma Matrizes 2x2");
    op.n1 = 0; // Não usamos
    op.n2 = 0;
    op.resultado = 0; // O resultado é uma matriz, não um número
    adicionarAoHistorico(op);
}

void multiplicaMatriz2x2Operacao() {
    printf("\n--------------------------------------------------\n");
    printf("            Multiplicacao de Matrizes 2x2\n");
    printf("--------------------------------------------------\n");

    double A[2][2], B[2][2], R[2][2];

    printf("--- Matriz A ---\n");
    lerMatriz2x2(A);
    printf("\n--- Matriz B ---\n");
    lerMatriz2x2(B);

    multiplicarMatrizes2x2(A, B, R); // Chama o cálculo

    printf("\n--- Resultado (A * B) ---\n");
    imprimirMatriz2x2(R);

    // Adicionando ao histórico (de forma simplificada)
    Operacao op;
    op.id = 24;
    strcpy(op.tipo, "Mult. Matrizes 2x2");
    op.n1 = 0;
    op.n2 = 0;
    op.resultado = 0;
    adicionarAoHistorico(op);
}


/**
 * Função que mostra o histórico formatado
 */
void exibirOperacao() {
    if (numOperacoes == 0) {
        printf("\nNao ha operacoes no historico.\n");
        return;
    }

    printf("\n--------------------------------------------------\n");
    printf("               Historico das Operacoes\n");
    printf("--------------------------------------------------\n");

    // Passa por cada operação salva
    for (int i = 0; i < numOperacoes; i++) {
        Operacao op = historico[i];
        // Imprime a parte comum
        printf("%03d) ID: %-2d | Tipo: %-25s | ", i + 1, op.id, op.tipo);

        // Esse switch-case é pra mostrar o histórico de um jeito bonitinho
        // pra cada tipo de operação, já que algumas só usam n1, outras usam n1 e n2...
        switch (op.id) {
            case 1:  // Adicao
            case 2:  // Subtracao
            case 3:  // Multiplicacao
            case 4:  // Divisao
                printf("Operandos: (%.2lf, %.2lf) | Resultado: %.2lf\n", op.n1, op.n2, op.resultado);
                break;
            case 5:  // Raiz Quadrada
            case 6:  // Raiz Cubica
            case 7:  // Seno
            case 8:  // Cosseno
            case 9:  // Tangente
            case 10: // Log10
            case 11: // LogN
            case 13: // Exponencial
            case 15: // ArcoSeno
            case 16: // ArcoCosseno
            case 17: // ArcoTangente
                printf("Operando: (%.2lf) | Resultado: %.2lf\n", op.n1, op.resultado);
                break;
            case 12: // Exponenciacao
                printf("Operandos: (Base: %.2lf, Exp: %.2lf) | Resultado: %.2lf\n", op.n1, op.n2, op.resultado);
                break;
            case 14: // Quadrado (lembra que salvamos n1 em n2?)
                printf("Operando: (%.2lf) | Resultado: %.2lf\n", op.n1, op.resultado);
                break;
            case 18: // Porcentagem (n1=valor, n2=%)
                printf("(%.2lf%% de %.2lf) | Resultado: %.2lf\n", op.n2, op.n1, op.resultado);
                break;
            case 19: // Desconto (n2=produto, n1=%)
                printf("(Produto: %.2lf, Desc: %.2lf%%) | Resultado: %.2lf\n", op.n2, op.n1, op.resultado);
                break;
            case 20: // C -> F
            case 21: // F -> C
                printf("Entrada: (%.2lf) | Resultado: %.2lf\n", op.n1, op.resultado);
                break;
            case 22: // Media (n1=N, n2=soma)
                printf("(%d numeros, Soma: %.2lf) | Resultado: %.2lf\n", (int)op.n1, op.n2, op.resultado);
                break;
            case 23: // Soma Matriz
            case 24: // Mult Matriz
                printf("Operacao com matrizes (ver resultado no console)\n");
                break;
            default:
                printf("Resultado: %.2lf\n", op.resultado);
        }
    }
}

// =================================================================
// --- Função Principal (main) ---
// =================================================================
//
// É aqui que o programa começa.
//
int main() {
    int opcao; // Guarda a escolha do menu
    int continuar; // Guarda se o usuário quer continuar (1=Sim, 0=Nao)

    // (BÔNUS) Tenta carregar o histórico do arquivo assim que o programa abre
    carregarHistoricoDoArquivo(NOME_ARQUIVO_HISTORICO);

    // Loop principal da calculadora
    do {
        // Imprime o menu
        printf("\n==================================================\n");
        printf("             CALCULADORA CIENTIFICA v2.0\n");
        printf("==================================================\n");
        printf("--- Operacoes Basicas ---\n");
        printf(" 1 - Adicao                 2 - Subtracao\n");
        printf(" 3 - Multiplicacao          4 - Divisao\n");
        printf("\n--- Operacoes Adicionais ---\n");
        printf(" 5 - Raiz Quadrada          6 - Raiz Cubica\n");
        printf(" 7 - Seno                   8 - Cosseno\n");
        printf(" 9 - Tangente               10 - Logaritmo Base 10\n");
        printf("11 - Logaritmo Natural      12 - Exponenciacao (X^Y)\n");
        printf("13 - Exponencial (e^X)      14 - Calculo Quadrado (X^2)\n");
        printf("15 - Arco Seno              16 - Arco Cosseno\n");
        printf("17 - Arco Tangente          18 - Porcentagem (Y%% de X)\n");
        printf("19 - Desconto               20 - Celsius para Fahrenheit\n");
        printf("21 - Fahrenheit para Celsius\n");
        printf("\n--- Funcoes de Array ---\n");
        printf("22 - Media de N numeros\n");
        printf("23 - Soma de Matrizes 2x2\n");
        printf("24 - Multiplicacao de Matrizes 2x2\n");
        printf("\n--- Sistema ---\n");
        printf("25 - Exibir Historico\n");
        printf(" 0 - Sair e Salvar Historico\n");
        printf("--------------------------------------------------\n");
        printf("Digite a opcao: ");

        // Validação da entrada do menu
        // Se o scanf falhar em ler 1 número...
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida! Por favor, digite um numero.\n");
            limparBufferEntrada(); // Limpa a sujeira
            continuar = 1; // Força o loop a rodar de novo
            continue;      // Pula pro início do 'do-while'
        }
        // Se deu certo, limpa o ENTER que sobrou
        limparBufferEntrada(); 

        // O 'switch' é tipo um monte de 'if'
        // Ele olha a 'opcao' e pula pro 'case' certo
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
            case 24: multiplicaMatriz2x2Operacao(); break;
            case 25: exibirOperacao(); break;
            case 0:
                printf("\n--------------------------------------------------\n");
                printf("Saindo da calculadora...\n");
                // (BÔNUS) Salva o histórico no arquivo antes de fechar
                salvarHistoricoEmArquivo(NOME_ARQUIVO_HISTORICO);
                printf("Ate mais!\n");
                printf("--------------------------------------------------\n");
                return 0; // Encerra o programa
            
            // 'default' é o que acontece se o usuário digita um número
            // que não está no menu (ex: 99)
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }

        printf("\n--------------------------------------------------\n");
        printf("Deseja fazer outro calculo? (1 para Sim / 0 para Nao): ");
        
        // (BUG CORRIGIDO: Adicionado limparBufferEntrada() aqui)
        if (scanf("%d", &continuar) != 1) {
            continuar = 0; // Se digitar algo errado (tipo 'a'), sai por segurança
        }
        limparBufferEntrada(); // Limpa o ENTER
        printf("\n");

    } while (continuar == 1); // Repete tudo se o usuário digitou 1
    
    // Se o usuário saiu (digitou 0 ou outra coisa), salva antes de fechar
    printf("\nSaindo da calculadora...\n");
    salvarHistoricoEmArquivo(NOME_ARQUIVO_HISTORICO);
    printf("Ate mais!\n");

    return 0; // Fim do programa
}