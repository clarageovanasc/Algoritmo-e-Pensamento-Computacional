PROJETO DE CALCULADORA EM C

Este é o nosso trabalho da disciplina de [coloque o nome da disciplina aqui]. 
É uma calculadora em C que funciona pelo terminal.

O programa mostra um menu com as opções de cálculo, o usuário escolhe o que quer fazer, digita os números e o programa mostra o resultado. Depois de cada conta, ele pergunta se a gente quer fazer outro cálculo ou sair.


O QUE A CALCULADORA FAZ
-----------------------
- Contas normais (soma, subtração, multiplicação e divisão).
- Raiz quadrada, raiz cúbica e potência.
- Contas de trigonometria (seno, cosseno, etc.).
- Logaritmo.
- Funções extras como porcentagem, desconto e conversão de temperatura.


COMO USAR
---------
1. Abra o terminal na pasta onde está o arquivo "calculadora.c".

2. Para compilar o programa, use o comando abaixo:
   (O -lm no final é importante porque usamos a biblioteca de matemática).

   gcc calculadora.c -o calculadora -lm

3. Para executar o programa depois de compilar, use:

   - No Windows:
     .\calculadora.exe
   

TECNOLOGIAS USADAS
------------------
- Linguagem C
- Compilador GCC
- Bibliotecas: stdio.h, stdlib.h, math.h
