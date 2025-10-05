#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

int main()
{
    int opcao;
    double n1, n2, resultado;
    int continuar;

do {
    printf("Escolha a operacao: \n");
    printf("1 - Adicao\n");
    printf("2 - Subtracao\n");
    printf("3 - Multiplicacao\n");
    printf("4 - Divisao\n");
    printf("5 - Raiz Quadrada\n");
    printf("6 - Raiz Cubica\n");
    printf("7 - Seno\n");
    printf("8 - Cosseno\n");
    printf("9 - Tangente\n");
    printf("10 - Logaritmo Base 10\n");
    printf("11 - Logaritmo Natural\n");
    printf("12 - Exponenciacao\n");
    printf("13 - Exponencial\n");
    printf("14 - Calculo do Quadrado\n");
    printf("15 - Arco Seno\n");
    printf("16 - Arco Cosseno\n");
    printf("17 - Arco Tangente\n");
    printf("18 - Porcentagem\n");
    printf("19 - Desconto\n");
    printf("20 - Celsius para Fahrenheit\n");
    printf("21 - Fahrenheit para Celsius\n");
    printf("Digite a opcao: \n");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        printf("Digite dois numeros: ");
        scanf("%lf %lf", &n1, &n2);
        resultado = n1 + n2;
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 2:
        printf("Digite dois numeros: ");
        scanf("%lf %lf", &n1, &n2);
        resultado = n1 - n2;
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 3:
        printf("Digite dois numeros: ");
        scanf("%lf %lf", &n1, &n2);
        resultado = n1 * n2;
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 4:
        printf("Digite dois numeros: ");
        scanf("%lf %lf", &n1, &n2);
        if (n2 != 0)
        {
            resultado = n1 / n2;
            printf("Resultado: %.2lf\n", resultado);
        }
        else
        {
            printf("Erro: Divisão por zero!\n");
        }
        break;
        
    case 5:
        printf("Digite um numero: ");
        scanf("%lf", &n1);
        if (n1 >= 0)
        {
            resultado = sqrt(n1);
            printf("Resultado: %.2lf\n", resultado);
        }
        else
        {
            printf("Erro: Raiz de número negativo!\n");
        }
        break;

    case 6:
        printf("Digite um numero: ");
        scanf("%lf", &n1);
        if (n1 >= 0)
        {
            resultado = cbrt(n1);
            printf("Resultado: %.2lf\n", resultado);
        }
        else
        {
            printf("Erro: Raiz de número negativo!\n");
        }
        break;

    case 7:
        printf("Digite o angulo em graus: ");
        scanf("%lf", &n1);
        resultado = sin(n1 * M_PI / 180);
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 8:
        printf("Digite o angulo em graus: ");
        scanf("%lf", &n1);
        resultado = cos(n1 * M_PI / 180);
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 9:
        printf("Digite o angulo em graus: ");
        scanf("%lf", &n1);
        resultado = tan(n1 * M_PI / 180);
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 10:
        printf("Digite o numero: ");
        scanf("%lf", &n1);
        if (n1 > 0)
        {
            resultado = log10(n1);
            printf("Resultado: %.2lf\n", resultado);
        }
        else
        {
            printf("Erro: Logaritmo de numero nao positivo!\n");
        }
        break;

    case 11:
        printf("Digite o numero: ");
        scanf("%lf", &n1);
        if (n1 > 0)
        {
            resultado = log(n1);
            printf("Resultado: %.2lf\n", resultado);
        }
        else
        {
            printf("Erro: Logaritmo de numero nao positivo!\n");
        }
        break;

    case 12:
        printf("Digite a base e o expoente: ");
        scanf("%lf %lf", &n1, &n2);
        resultado = pow(n1, n2);
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 13:
        printf("Digite o expoente x para e^x: ");
        scanf("%lf", &n1);
        resultado = exp(n1);
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 14:
        printf("Digite o numero: ");
        scanf("%lf", &n1);
        resultado = n1 * n1;
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 15:
        printf("Digite o valor entre -1 e 1 para calcular o Arco Seno: ");
        scanf("%lf", &n1);
        if (n1 >= -1 && n1 <= 1)
        {
            resultado = asin(n1) * 180 / M_PI;
            printf("Resultado: %.2lf\n", resultado);
        }
        else
        {
            printf("Erro: O valor para o Arco Seno deve estar entre -1 e 1.\n");
        }
        break;

    case 16:
        printf("Digite o valor entre -1 e 1 para calcular o Arco Cosseno: ");
        scanf("%lf", &n1);
        if (n1 >= -1 && n1 <= 1)
        {
            resultado = acos(n1) * 180 / M_PI;
            printf("Resultado: %.2lf\n", resultado);
        }
        else
        {
            printf("Erro: O valor para o Arco Cosseno deve estar entre -1 e 1.\n");
        }
        break;

    case 17:
        printf("Digite um valor para calcular o Arco Tangente: ");
        scanf("%lf", &n1);
        resultado = atan(n1) * 180 / M_PI;
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 18:
        printf("Digite o valor percentual (n1) e o valor base (n2): ");
        scanf("%lf %lf", &n1, &n2);
        resultado = (n1 / 100.0) * n2;
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 19:
        printf("Digite o valor percentual (n1) e o valor do produto(n2): ");
        scanf("%lf %lf", &n1, &n2);
        resultado = n2 - ((n1 * n2) / 100.0);
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 20:
        printf("Digite o valor de Celsius: ");
        scanf("%lf", &n1);
        resultado = (n1 * 1.8) + 32;
        printf("Resultado: %.2lf\n", resultado);
        break;

    case 21:
        printf("Digite o valor de Fahrenheit(A partir de 32): ");
        scanf("%lf", &n1);
        resultado = (n1 - 32) * 5 / 9;
        printf("Resultado %.2lf\n", resultado);
        break;

    default:

        printf("Opcao invalida!\n");
        break;
}
printf("\nDeseja fazer outro calculo? (1 para Sim / 0 para Nao): ");
        scanf("%d", &continuar);
        printf("\n");

    } while (continuar == 1);

return 0; 
}