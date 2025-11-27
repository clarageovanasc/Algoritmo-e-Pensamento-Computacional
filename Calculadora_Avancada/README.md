🔬 Calculadora Científica & Matricial em C

Projeto final da disciplina de Algoritmos, desenvolvido em colaboração (Pair Programming). Este software vai além das operações básicas, implementando funções científicas, cálculos matriciais e persistência de dados (histórico salvo em arquivo).

🚀 Funcionalidades do Sistema

O sistema conta com 25 funcionalidades divididas em módulos:

🧮 Aritmética e Álgebra

Básicos: Adição, Subtração, Multiplicação, Divisão.

Avançados: Potenciação (pow), Raiz Quadrada (sqrt), Raiz Cúbica (cbrt), Exponencial (exp), Logaritmos (Base 10 e Natural).

Financeiro: Cálculo de Porcentagem e Descontos.

📐 Trigonometria

Seno, Cosseno, Tangente.

Funções inversas: Arco Seno, Arco Cosseno, Arco Tangente.

Nota: Conversão automática de graus para radianos para precisão dos cálculos.

📊 Estatística e Matrizes

Média Aritmética: Suporta input dinâmico de até 100 números.

Álgebra Linear: Soma e Multiplicação de Matrizes 2x2.

💾 Persistência de Dados (Diferencial)

Histórico Automático: Todas as operações são salvas em memória durante a execução.

Exportação CSV: Ao fechar o programa, o histórico é salvo no arquivo historico.csv, permitindo que os dados sejam abertos posteriormente no Excel.

Recuperação: Ao abrir o programa, ele lê o arquivo anterior e restaura o histórico.

💻 Destaques Técnicos (Code Review)

O código demonstra domínio de conceitos avançados da Linguagem C:

Structs (Estruturas de Dados):
Utilizamos typedef struct para criar tipos complexos, organizando as operações e as matrizes de forma lógica.

typedef struct {
    char tipo[50];
    double n1, n2, resultado;
    Matriz2x2 resultadoMatriz;
} Operacao;


Manipulação de Arquivos (File I/O):
Uso das funções fopen, fprintf e fscanf para garantir que os dados não sejam perdidos ao fechar o terminal.

Tratamento de Erros e Buffer:
Implementação da função limparBufferEntrada() para evitar "lixo de memória" no scanf, e validações matemáticas robustas (ex: proibição de divisão por zero ou raiz de número negativo).

🛠️ Tecnologias e Bibliotecas

Linguagem C (Padrão C99)

<math.h>: Para cálculos científicos complexos.

<string.h>: Para manipulação de nomes das operações.

<stdio.h> & <stdlib.h>: Entrada/Saída e alocação.

⚙️ Como Executar

Compilação:
É necessário linkar a biblioteca matemática (-lm) dependendo do compilador (especialmente no Linux/GCC).

gcc main.c -o calculadora -lm


Execução:

./calculadora


Verificando o Histórico:
Após realizar cálculos e sair (Opção 0), verifique o arquivo historico.csv criado na mesma pasta.

👥 Autoria e Colaboração

Este projeto foi desenvolvido em conjunto, unindo lógica de programação e organização de software.

Colaborador

Função Principal

João Paulo

Core Developer & Arquiteto de Software. Responsável pela implementação da lógica matemática complexa, manipulação de ponteiros e estruturação do sistema de arquivos (CSV).

Clara Geovana

Co-Developer & Documentação. Responsável pela revisão de código, implementação de validações de input, testes de usabilidade e documentação técnica (README).

Desenvolvido para a Avaliação A1 de Algoritmos e Pensamento Computacional.
