#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

typedef struct {
    double elementos[2][2];
} Matriz2x2;

typedef struct{
    char tipo[50];
    double n1, n2;
    double resultado;
    int id;
    Matriz2x2 resultadoMatriz;
} Operacao;

#define MAX_HISTORICO 100
Operacao historico[MAX_HISTORICO];
int numOperacoes = 0;

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
} 
    
void adicionarAoHistorico(Operacao op) {
    if (numOperacoes < MAX_HISTORICO) {
        historico[numOperacoes] = op;
        numOperacoes++;
    } else {
        printf("Historico cheio! A operacao antiga foi removida.\n");

        for (int i = 0; i < MAX_HISTORICO - 1; i++) {
            historico[i] = historico[i + 1];
        }
        historico[MAX_HISTORICO - 1] = op;
    }
}

void lerMatriz2x2(Matriz2x2 *matriz, const char *nome) {
    int ler;
    printf("Digite os elementos da Matriz %s (2x2):\n", nome);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            do {
                printf("Elemento [%d][%d]: ", i + 1, j + 1);
                ler = scanf("%lf", &matriz->elementos[i][j]);
                if (ler != 1) {
                    printf("Erro! Isso nao e um numero.\n");
                    limparBufferEntrada();
                }
            } while (ler != 1);
        }
    }
}

// Funcao auxiliar para exibir uma matriz 2x2
void exibirMatriz2x2(Matriz2x2 matriz) {
    printf("[ %.2lf  %.2lf ]\n", matriz.elementos[0][0], matriz.elementos[0][1]);
    printf("[ %.2lf  %.2lf ]\n", matriz.elementos[1][0], matriz.elementos[1][1]);
}

void adicaoOperacao() {
    double operandos[2]; 
    Operacao op; 
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                   Adicao\n");
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
    
    op.resultado = op.n1 + op.n2;
    
        strcpy(op.tipo, "Adicao");
        op.id = 1;
    
            printf("\nResultado: %.2lf + %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    
            adicionarAoHistorico(op);
}

void subtracaoOperacao() {
    double operandos[2]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                   Subtracao\n");
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
    
    op.resultado = op.n1 - op.n2;
    
        strcpy(op.tipo, "Subtracao");
        op.id = 2;
    
            printf("\nResultado: %.2lf - %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    
            adicionarAoHistorico(op);
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
    
    op.resultado = op.n1 * op.n2;
    
        strcpy(op.tipo, "Multiplicacao");
        op.id = 3;
    
            printf("\nResultado: %.2lf * %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    
            adicionarAoHistorico(op);
}

void divisaoOperacao() {
    double operandos[2]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                    Divisao\n");
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
        
        if (i == 1) {

            while (operandos[1] == 0.0) {
                printf("Erro: Divisao por zero!\n");
                printf("\nDigite o segundo numero novamente: \n");
                
                do {
                    ler = scanf("%lf", &operandos[1]);
                    if (ler != 1) {
                        printf("Erro! Isso nao e um numero.\n");
                        limparBufferEntrada();
                }
            } while (ler != 1);
        }
    }
}
    
    op.n1 = operandos[0]; 
    op.n2 = operandos[1];
    
    op.resultado = op.n1 / op.n2;
    
        strcpy(op.tipo, "Divisao");
        op.id = 4;
    
            printf("\nResultado: %.2lf / %.2lf = %.2lf \n", op.n1, op.n2, op.resultado);
    
            adicionarAoHistorico(op);
}

void raizquadradaOperacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                    Raiz Quadrada\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o numero: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
        
        if (i == 0) {

            while (operandos[0] <= 0.0) {
                printf("Erro: Número Negativo!!\n");
                printf("\nDigite o segundo número novamente: \n");
                
                do {
                    ler = scanf("%lf", &operandos[0]);
                    if (ler != 1) {
                        printf("Erro! Isso nao e um numero.\n");
                        limparBufferEntrada();
                }
            } while (ler != 1);
        }
    }
}
    
    op.n1 = operandos[0]; 
    
    op.resultado = sqrt(op.n1);
    
        strcpy(op.tipo, "Raiz Quadrada");
        op.id = 5;
    
            printf("Resultado: √%.2lf = %.2lf\n",op.n1, op.resultado);
    
            adicionarAoHistorico(op);
}

void raizcubicaOperacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                   Raiz Cubica\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o numero: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
    }
    
    op.n1 = operandos[0]; 
    
    op.resultado = cbrt(op.n1);
    
        strcpy(op.tipo, "Raiz Cubica");
        op.id = 6;
    
            printf("Resultado: 3√%.2lf = %.2lf\n",op.n1, op.resultado);
    
            adicionarAoHistorico(op);
}


void senoOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                      Seno\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o angulo em graus: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
    }
    
    op.n1 = operandos[0]; 
    
    op.resultado = sin(op.n1 * M_PI / 180);
    
        strcpy(op.tipo, "Seno");
        op.id = 7;
    
            printf("Resultado: %.2lf * PI / 180 = %.2lf\n", op.n1, op.resultado);
            
            adicionarAoHistorico(op);
}

void cossenoOperacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                      Cosseno\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o angulo em graus: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
    }
    
    op.n1 = operandos[0]; 
    
    op.resultado = cos(op.n1 * M_PI / 180);
    
        strcpy(op.tipo, "Cosseno");
        op.id = 8;
    
            printf("Resultado: %.2lf * PI / 180 = %.2lf\n", op.n1, op.resultado);
            
            adicionarAoHistorico(op);
}

void tangenteOperacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                      Tangente\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o angulo em graus: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
    }
    
    op.n1 = operandos[0]; 
    
    op.resultado = tan(op.n1 * M_PI / 180);
    
        strcpy(op.tipo, "Tangente");
        op.id = 9;
    
            printf("Resultado: %.2lf * PI / 180 = %.2lf\n", op.n1, op.resultado);
            
            adicionarAoHistorico(op);
}

void logbase10Operacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                Logaritmo Base 10\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o logaritmo: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
        
        if (i == 0) {

            while (operandos[0] <= 0.0) {
                printf("Erro: O numero do logaritmo nao pode ser negativo!\n");
                printf("\nDigite o logaritmo novamente: \n");
                
                do {
                    ler = scanf("%lf", &operandos[0]);
                    if (ler != 1) {
                        printf("Erro! Isso nao e um numero.\n");
                        limparBufferEntrada();
                }
            } while (ler != 1);
        }
    }
}
    
    op.n1 = operandos[0]; 
    
    op.resultado = log10(op.n1);
        
        strcpy(op.tipo, "Logaritmo Base 10");
        op.id = 10;
        
                printf("Resultado: log10(%.2lf) = %.2lf\n", op.n1, op.resultado);
            
                adicionarAoHistorico(op);
}

void lognaturalOperacao() {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                Logaritmo Natural\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o logaritmo: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
        
        if (i == 0) {

            while (operandos[0] <= 0.0) {
                printf("Erro: O numero do logaritmo nao pode ser negativo!\n");
                printf("\nDigite o logaritmo novamente: \n");
                
                do {
                    ler = scanf("%lf", &operandos[0]);
                    if (ler != 1) {
                        printf("Erro! Isso nao e um numero.\n");
                        limparBufferEntrada();
                }
            } while (ler != 1);
        }
    }
}
    
    op.n1 = operandos[0]; 
    
    op.resultado = log(op.n1);
        
        strcpy(op.tipo, "Logaritmo Natural");
        op.id = 11;
        
                printf("Resultado: ln(%.2lf) = %.2lf\n", op.n1, op.resultado);
            
                adicionarAoHistorico(op);
}

void exponenciacaoOperacao () {
    double operandos[2]; 
    Operacao op; 
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                  Exponenciacao\n");
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
    
    op.resultado = pow(op.n1, op.n2);
    
            strcpy(op.tipo, "Exponenciacao");
            op.id = 12;
            
                    printf("Resultado: %.2lf\n", op.resultado);
    
            adicionarAoHistorico(op);
}

void exponencialOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                    Exponencial\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o numero: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
        
        if (i == 0) {

            while (operandos[0] == 0.0) {
                printf("Erro: O numero do exponencial nao pode ser negativo!\n");
                printf("\nDigite o numero novamente: \n");
                
                do {
                    ler = scanf("%lf", &operandos[0]);
                    if (ler != 1) {
                        printf("Erro! Isso nao e um numero.\n");
                        limparBufferEntrada();
                }
            } while (ler != 1);
        }
    }
}
    
    op.n1 = operandos[0]; 
    
    op.resultado = exp(op.n1);
    
            strcpy(op.tipo, "Exponencial");
            op.id = 13;
            
                    printf("Resultado: %.2lf\n", op.resultado);
    
            adicionarAoHistorico(op);
}

void calculoquadradoOperacao () {
    double operandos[1]; 
    Operacao op; 
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                   Calculo Quadrado\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o numero: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
    }
    
    op.n1 = operandos[0]; 
    
    op.resultado = op.n1 * op.n1;
    
        strcpy(op.tipo, "Calculo Quadrado");
        op.id = 14;
    
            printf("\nResultado: %.2lf * %.2lf = %.2lf \n", op.n1, op.n1, op.resultado);
    
            adicionarAoHistorico(op);
}

void arcosenoOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                    Arco Seno\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o valor entre -1 e 1 para calcular o Arco Seno: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
        
        if (i == 0) {

            while (operandos[0] < -1 || operandos [0] > 1) {
                printf("Erro: O valor para o Arco Seno deve estar entre -1 e 1.\n");
                printf("\nDigite o valor novamente: \n");
                
                do {
                    ler = scanf("%lf", &operandos[0]);
                    if (ler != 1) {
                        printf("Erro! Isso nao e um numero.\n");
                        limparBufferEntrada();
                }
            } while (ler != 1);
        }
    }
}
    
    op.n1 = operandos[0]; 
    
    op.resultado = asin(op.n1) * 180 / M_PI;
    
        strcpy(op.tipo, "Arco Seno");
        op.id = 15;
        
            printf("Resultado: %.2lf * 180 / PI = %.2lf\n", op.n1, op.resultado);
    
            adicionarAoHistorico(op);
}

void arcocossenoOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                    Arco Cosseno\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o valor entre -1 e 1 para calcular o Arco Cosseno: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
        
        if (i == 0) {

            while (operandos[0] < -1 || operandos [0] > 1) {
                printf("Erro: O valor para o Arco Cosseno deve estar entre -1 e 1.\n");
                printf("\nDigite o valor novamente: \n");
                
                do {
                    ler = scanf("%lf", &operandos[0]);
                    if (ler != 1) {
                        printf("Erro! Isso nao e um numero.\n");
                        limparBufferEntrada();
                }
            } while (ler != 1);
        }
    }
}
    
    op.n1 = operandos[0]; 
    
    op.resultado = acos(op.n1) * 180 / M_PI;
    
        strcpy(op.tipo, "Arco Cosseno");
        op.id = 16;
        
            printf("Resultado: %.2lf * 180 / PI = %.2lf\n", op.n1, op.resultado);
    
            adicionarAoHistorico(op);
}

void arcotanOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                    Arco Tangente\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o valor para calcular o Arco Tangente: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
    }
    
    op.n1 = operandos[0]; 
    
    op.resultado = atan(op.n1) * 180 / M_PI;
    
        strcpy(op.tipo, "Arco Tangente");
        op.id = 17;
        
            printf("Resultado: %.2lf * 180 / PI = %.2lf\n", op.n1, op.resultado);
    
            adicionarAoHistorico(op);
}

void porcentagemOperacao () {
    double operandos[2]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                    Porcentagem\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 2; i++) {
        do {
            printf("Digite %s: \n", (i == 0) ? "o Valor" : "a Porcentagem");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
        
        if (i == 1) {

            while (operandos[1] > 100 || operandos[1] < 0) {
                printf("Erro: A porcentagem nao pode ultrapassar de 100.\n");
                printf("\nDigite a porcentagem novamente: \n");
                
                do {
                    ler = scanf("%lf", &operandos[1]);
                    if (ler != 1) {
                        printf("Erro! Isso nao e um numero.\n");
                        limparBufferEntrada();
                }
            } while (ler != 1);
        }
    }
}
    
    op.n1 = operandos[0]; 
    op.n2 = operandos[1];
    
    op.resultado = (op.n2 / 100.0) * op.n1;
            
        strcpy(op.tipo, "Porcentagem");
        op.id = 18;
                    
            printf("Resultado: %.2lf / 100 * %.2lf = %.2lf\n", op.n2, op.n1, op.resultado);
    
            adicionarAoHistorico(op);
}

void descontoOperacao () {
    double operandos[2]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                    Desconto\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 2; i++) {
        do {
            printf("Digite %s: \n", (i == 0) ? "o Valor do Desconto" : "o Valor do Produto");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
        
        if (i == 0) {

            while (operandos[0] > 100 || operandos[0] < 0) {
                printf("Erro: O desconto nao pode ultrapassar de 100 e não pode ser negativo.\n");
                printf("\nDigite o desconto novamente: \n");
                
                do {
                    ler = scanf("%lf", &operandos[0]);
                    if (ler != 1) {
                        printf("Erro! Isso nao e um numero.\n");
                        limparBufferEntrada();
                }
            } while (ler != 1);
        }
    }
}
    
    op.n1 = operandos[0]; 
    op.n2 = operandos[1];
    
    op.resultado = op.n2 - ((op.n1 * op.n2) / 100.0);
    
        strcpy(op.tipo, "Desconto");
        op.id = 19;
        
            printf("Resultado: %.2lf - %.2lf * %.2lf / 100 = %.2lf (preço final com desconto).\n", op.n2, op.n1, op.n2, op.resultado);
    
            adicionarAoHistorico(op);
}

void celparafahOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                Celsius para Fahrenheit\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o valor de Celsius: \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
    }
    
    op.n1 = operandos[0]; 
    
    op.resultado = (op.n1 * 1.8) + 32;
    
        strcpy(op.tipo, "Celsius para Fahrenheit");
        op.id = 20;
                
                printf("Resultado: %.2lf * 1.8 + 32 = %.2lf\n", op.n1, op.resultado);
    
            adicionarAoHistorico(op);
}

void fahparacelOperacao () {
    double operandos[1]; 
    Operacao op;
    int ler;
    
    printf("\n--------------------------------------------------\n");
    printf("                Fahrenheit para Celsius\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < 1; i++) {
        do {
            printf("Digite o valor de Fahrenheit(A partir de 32): \n");
            
            ler = scanf("%lf", &operandos[i]); 
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
        
        if (i == 0) {

            while (operandos[0] < 32) {
                printf("Erro: O valor de Fahrenheit esta menor que 32.\n");
                printf("\nDigite o valor novamente: \n");
                
                do {
                    ler = scanf("%lf", &operandos[0]);
                    if (ler != 1) {
                        printf("Erro! Isso nao e um numero.\n");
                        limparBufferEntrada();
                }
            } while (ler != 1);
        }
    }
}
    
    op.n1 = operandos[0]; 
    
    op.resultado = (op.n1 - 32) * 5 / 9;
    
        strcpy(op.tipo, "Fahrenheit para Celsius");
        op.id = 21;
        
            printf("Resultado: %.2lf - 32 * 5 / 9 = %.2lf\n", op.n1, op.resultado);
    
            adicionarAoHistorico(op);
}

void mediaOperacao () {
    int N;
    int ler;
    double numero, soma = 0.0, media;
    Operacao op;

    printf("\n--------------------------------------------------\n");
    printf("                      Media\n");
    printf("--------------------------------------------------\n");

    do {
        printf("Quantos numeros voce deseja para calcular a media? (maximo 100): \n");
        ler = scanf("%d", &N);
        
        if (ler != 1 || N <= 0 || N > 100) {
            printf("Erro! Digite um numero inteiro positivo (maximo 100).\n");
            limparBufferEntrada();
            ler = 0; 
        }
    } while (ler != 1 || N <= 0 || N > 100);
    
    for (int i = 0; i < N; i++) {
        do {
            printf("Digite o %d numero: \n", i + 1);
            ler = scanf("%lf", &numero);
            
            if (ler != 1) {
                printf("Erro! Isso nao e um numero.\n");
                limparBufferEntrada();
            }
        } while (ler != 1);
        soma += numero;
    }
    
    if (N > 0) {
        media = soma / N;
    } else {
        media = 0.0;
    }

    op.n1 = (double)N; 
    op.n2 = 0.0; 
    op.resultado = media;
    
    strcpy(op.tipo, "Media");
    op.id = 22;
    
    printf("\nResultado: A media de %d numeros e %.2lf \n", N, op.resultado);
    
    adicionarAoHistorico(op);
    limparBufferEntrada(); 
}

void somaMatriz2x2Operacao() {
    Matriz2x2 matA, matB, matResultante;
    Operacao op;

    printf("\n--------------------------------------------------\n");
    printf("             Soma de Matriz 2x2\n");
    printf("--------------------------------------------------\n");

    lerMatriz2x2(&matA, "A");
    lerMatriz2x2(&matB, "B");

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matResultante.elementos[i][j] = matA.elementos[i][j] + matB.elementos[i][j];
        }
    }

    strcpy(op.tipo, "Soma de Matriz 2x2");
    op.id = 23;
    op.n1 = 0.0;
    op.n2 = 0.0;
    op.resultado = 0.0;
    op.resultadoMatriz = matResultante;

    printf("\nMatriz Resultante (A + B):\n");
    exibirMatriz2x2(matResultante);
    printf("\n");

    adicionarAoHistorico(op);
    limparBufferEntrada();
}

void multiplicacaoMatriz2x2Operacao() {
    Matriz2x2 matA, matB, matResultante;
    Operacao op;

    printf("\n--------------------------------------------------\n");
    printf("             Multiplicacao de Matriz 2x2\n");
    printf("--------------------------------------------------\n");

    lerMatriz2x2(&matA, "A");
    lerMatriz2x2(&matB, "B");

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matResultante.elementos[i][j] = 0.0;
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                matResultante.elementos[i][j] += matA.elementos[i][k] * matB.elementos[k][j];
            }
        }
    }

    strcpy(op.tipo, "Multiplicacao de Matriz 2x2");
    op.id = 24;
    op.n1 = 0.0;
    op.n2 = 0.0;
    op.resultado = 0.0;
    op.resultadoMatriz = matResultante;

    printf("\nMatriz Resultante (A * B):\n");
    exibirMatriz2x2(matResultante);
    printf("\n");

    adicionarAoHistorico(op);
    limparBufferEntrada();
}

void exibirOperacao() {
    if (numOperacoes == 0) {
        printf("Nao ha operacoes feitas ainda.\n");
        return;
    }

    printf("--------------------------------------------------\n");
    printf("            Historico das Operacoes\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < numOperacoes; i++) {
        Operacao op = historico[i];
        printf("%03d) Tipo: %-25s | ", i + 1, op.tipo);

        if (op.id == 1) {
            printf("Resultado: %2.lf + %2.lf = %2.lf \n", op.n1, op.n2, op.resultado);
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
            printf("Resultado: %.2lf * PI / 180 = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 8) {
            printf("Resultado: %.2lf * PI / 180 = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 9) {
            printf("Resultado: %.2lf * PI / 180 = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 10) {
            printf("Resultado: log10(%.2lf) = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 11) {
            printf("Resultado: ln(%.2lf) = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 12) {
            printf("Resultado: %.2lf\n", op.resultado);
        } else if (op.id == 13) {
            printf("Resultado: %.2lf\n", op.resultado);
        } else if  (op.id == 14) {
            printf("Resultado: %.2lf * %.2lf = %.2lf\n", op.n1, op.n1, op.resultado);
        } else if (op.id == 15) {
            printf("Resultado: %.2lf * 180 / PI = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 16) {
            printf("Resultado: %.2lf * 180 / PI = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 17) {
            printf("Resultado: %.2lf * 180 / PI = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 18) {
            printf("Resultado: %.2lf / 100 * %.2lf = %.2lf\n", op.n2, op.n1, op.resultado);
        } else if (op.id == 19) {   
            printf("Resultado: %.2lf - %.2lf * %.2lf / 100 = %.2lf preço final com desconto.\n", op.n2, op.n1, op.n2, op.resultado);
        } else if (op.id == 20) {
            printf("Resultado: %.2lf * 1.8 + 32 = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 21) {
            printf("Resultado: %.2lf  - 32 * 5 / 9 = %.2lf\n", op.n1, op.resultado);
        } else if (op.id == 22) {
            printf("Resultado: A media de %d numeros e %.2lf\n", (int)op.n1, op.resultado);
        } else if (op.id == 23) { 
            printf("Resultado da Soma:\n");
            printf("                                                [ %.2lf  %.2lf ]\n", op.resultadoMatriz.elementos[0][0], op.resultadoMatriz.elementos[0][1]);
            printf("                                                [ %.2lf  %.2lf ]\n", op.resultadoMatriz.elementos[1][0], op.resultadoMatriz.elementos[1][1]);
        } else if (op.id == 24) {
            printf("Resultado da Multiplicacao:\n");
            printf("                                                [ %.2lf  %.2lf ]\n", op.resultadoMatriz.elementos[0][0], op.resultadoMatriz.elementos[0][1]);
            printf("                                                [ %.2lf  %.2lf ]\n", op.resultadoMatriz.elementos[1][0], op.resultadoMatriz.elementos[1][1]);
        }
    }
}  

int main()
{
    int opcao;
    double n1, n2;
    double resultado;
    int continuar;

do {
    printf("--------------------------------------------------\n");
    printf("              CALCULADORA CIENTIFICA\n");
    printf("--------------------------------------------------\n");
    printf("\nOpcoes: \n");
    printf("\n--------------------------------------------------\n");
    printf("                Operacoes Basicas\n");
    printf("--------------------------------------------------\n");
    printf("1 - Adicao\n");
    printf("2 - Subtracao\n");
    printf("3 - Multiplicacao\n");
    printf("4 - Divisao\n");
    printf("\n--------------------------------------------------\n");
    printf("                Operacoes Adicionais\n");
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
    printf("                    Matriz\n");
    printf("--------------------------------------------------\n");
    printf("23 - Soma de Matriz 2x2\n");
    printf("24 - Multiplicacao de Matriz 2x2\n");
    printf("\n--------------------------------------------------\n");
    printf("                    Historico\n");
    printf("--------------------------------------------------\n");
    printf("25 - Historico\n");
    printf("\n--------------------------------------------------\n");
    printf("               SAIR DA CALCULADORA\n");
    printf("--------------------------------------------------\n");
    printf("0 - Para sair\n");
    printf("\n--------------------------------------------------\n");
    printf("Digite a opcao: \n");
    scanf("%d", &opcao);

        limparBufferEntrada();

    switch (opcao) {
    case 1:
        adicaoOperacao();
        break;

    case 2:
        subtracaoOperacao();
        break;

    case 3:
        multiplicacaoOperacao();
        break;

    case 4:
        divisaoOperacao();
        break;
        
    case 5:
        raizquadradaOperacao();
        break;

    case 6:
        raizcubicaOperacao();
        break;

    case 7:
        senoOperacao();
        break;

    case 8:
        cossenoOperacao();
        break;

    case 9:
        tangenteOperacao();
        break;

    case 10:
        logbase10Operacao();
        break;

    case 11:
        lognaturalOperacao();
        break;

    case 12:
        exponenciacaoOperacao();
        break;

    case 13:
        exponencialOperacao();
        break;

    case 14:
        calculoquadradoOperacao();
        break;

    case 15:
        arcosenoOperacao();
        break;

    case 16:
        arcocossenoOperacao();
        break;

    case 17:
        arcotanOperacao();
        break;

    case 18:
        porcentagemOperacao();
        break;

    case 19:
        descontoOperacao();
        break;

    case 20:
        celparafahOperacao();
        break;

    case 21:
        fahparacelOperacao();
        break;

    case 22:
        mediaOperacao();
        break;
    
    case 23:
        somaMatriz2x2Operacao();
        break;
    
    case 24:
        multiplicacaoMatriz2x2Operacao();
        break;
        
    case 25:
        exibirOperacao();
        break;
        
    case 0:
        printf("\n--------------------------------------------------\n");
        printf("          Saindo da calcluadora! Ate mais.\n");
        printf("--------------------------------------------------\n");
            return 0;
        break;
        
    default:

        printf("Opcao invalida!\n");
        break;
}
printf("\n--------------------------------------------------\n");
printf("Deseja fazer outro calculo ou ver o historico? (1 para Sim/ 0 para Nao): ");
        scanf("%d", &continuar);

    } while (continuar == 1);

return 0; 
}
