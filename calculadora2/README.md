Calculadora em C 2.0
Matéria - Algoritmos e Pensamento Computacional.

É uma calculadora que a gente fez em C e que roda direto no terminal.

O que o programa faz?
É uma calculadora semicientífica.

Funções:

Contas simples (soma, subtração, divisão, etc.)

Funções mais complicadas (raiz quadrada, raiz cúbica, seno, cosseno, logaritmo, potência)

Coisas que usam arrays (tipo média de vários números e contas com matriz 2x2)

Converte temperatura (C para F e F para C) e calcula desconto.

O mais legal é que ela salva um histórico de tudo o que você fez em um arquivo historico.csv. Quando você abre o programa de novo, o histórico antigo aparece lá.

Como rodar a calculadora?
Dentro do VS Code:
No VS Code, vá em File > Open Folder... e abra a pasta onde o seu main.c está (ex: a pasta calculadora2.c).

Com a sua pasta aberta, vá no menu lá em cima e clique em Terminal > New Terminal.

Vai aparecer um terminal na parte de baixo do VS Code. Ele já vai estar dentro da pasta certa.

Nesse terminal, digite o comando para compilar:

Bash

gcc main.c -o calculadora -lm
(Aperte Enter. Se não aparecer nenhuma mensagem de erro vermelha, deu certo).

Agora, na mesma linha, digite o comando para rodar o programa:

Bash

./calculadora
(Ou .\calculadora.exe se você estiver no Windows).

Pronto! O seu programa vai rodar ali mesmo, no terminal do VS Code.

Feito por:
João Paulo Costa de Paula 
Clara Geovana Caldeira da Silva